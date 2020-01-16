#include "Mixer.hpp"
#include <mutex>
#include <portaudio.h>
#include <vector>

namespace tsal {

void Mixer::paStreamFinished(void* userData) {
  (void) userData;
  return;
}

int Mixer::paCallback( const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags,
                       void *userData ) {
  (void) timeInfo; /* Prevent unused variable warnings. */
  (void) statusFlags;
  (void) inputBuffer;

  Mixer *mixer = static_cast<Mixer *>(userData);
  return mixer->audioCallback((float*) outputBuffer, framesPerBuffer);
}

int Mixer::audioCallback(float *outputBuffer, unsigned long frameCount) {
  mProcessing = true;
  const auto channels = mContext.getChannelCount();
  mBuffer.setSize(frameCount, channels);
  mBuffer.clear();
  mMaster.getOutput(mBuffer);
  for (unsigned long i = 0; i < frameCount; i++) {
    mSequencer.tick();
    for (unsigned j = 0; j < channels; j++) {
      outputBuffer[i * channels + j] = mBuffer[i * channels + j];
    }
  }
  // Update the model
  runModelChanges();
  
  return paContinue;
}

void Mixer::openPaStream() {
  PaError err = Pa_Initialize();
  if (err != paNoError) {
    return;
  }
  PaStreamParameters outputParameters;

  const PaDeviceIndex index = Pa_GetDefaultOutputDevice();
  outputParameters.device = index;
  if (outputParameters.device == paNoDevice) {
    printf("No default output device found\n");
    return;
  }

  const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
  if (pInfo != 0) {
    printf("Output device name: '%s'\n", pInfo->name);
    printf("Default sample rate: '%f'\n", pInfo->defaultSampleRate);
  }

  outputParameters.channelCount = mContext.getChannelCount();
  outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;

  mSequencer.setSampleRate(mContext.getSampleRate());
  mSequencer.setBPM(60);
  mSequencer.setPPQ(240);

  // Add a compressor so people don't break their sound cards
  // mMaster.add(mCompressor);
  err = Pa_OpenStream(&mPaStream,
                      NULL, /* no input */
                      &outputParameters,
                      mContext.getSampleRate(),
                      paFramesPerBufferUnspecified,
                      paClipOff,      /* we won't output out of range samples so don't bother clipping them */
                      &Mixer::paCallback,
                      this
                      );

  if (err != paNoError) {
    /* Failed to open stream to device !!! */
    return;
  }

  err = Pa_SetStreamFinishedCallback(mPaStream, &Mixer::paStreamFinished);

  if (err != paNoError) {
    Pa_CloseStream(mPaStream);
    mPaStream = 0;
    return;
  }
  err = Pa_StartStream(mPaStream);
  if (err != paNoError) {
    return;
  }

  mMaster.updateContext(mContext);
}

Mixer::Mixer() : mContext(44100, 2, this) {
  openPaStream();
}

/**
 * @brief Construct a new Mixer
 * 
 * @param sampleRate if default constructor is used, Mixer will default to the highest sample rate supported
 */
Mixer::Mixer(unsigned sampleRate) : mContext(sampleRate, 2, this) {
  openPaStream();
}

Mixer::~Mixer() {
  PaError err = Pa_CloseStream(mPaStream);
  if (err != paNoError) {
    return;
  }
  err = Pa_Terminate();
  if (err != paNoError) {
    return;
  }
}

/**
 * @brief Make a change to the DAW model
 * Since the callback function can be accessing any given device in the DAW (channel, instrument, effect),
 * changes to this model have to be mutually exclusive from the sound device callback
 * 
 * @param change a function that is executed safely for making model changes
 */
void Mixer::requestModelChange(std::function<void()> change) {
  // This is currently a pretty naive implementation
  // It assumes that the audio callback function is constantly being run
  
  // Increment the model change request count
  std::unique_lock<std::mutex> changeLock(mChangeRequestMutex);
  mChangeRequests++;
  changeLock.unlock();

  // Start the critical section for the change
  std::unique_lock<std::mutex> modelLock(mModelMutex);
  mModelChangeRequestCondition.wait(modelLock);

  // We can safely modify the model
  change();
  
  changeLock.lock();
  bool moreChanges = --mChangeRequests;
  changeLock.unlock();

  // Check if there are no more changes
  if (!moreChanges) {
    mWaitModelChangeCondition.notify_one();
  } else {
    modelLock.unlock();
    mModelChangeRequestCondition.notify_one();
  }
}

/**
 * @brief Run the scheduled changes to the model
 *
 */
void Mixer::runModelChanges() {
  // Check if there are requests to change the model
  if (mChangeRequests) {
    std::unique_lock<std::mutex> lk(mWaitModelChangeMutex);
    mModelChangeRequestCondition.notify_one();
    mWaitModelChangeCondition.wait(lk);
  }
}

/**
 * @brief Add a channel 
 *
 * @param channel
 */
void Mixer::add(Channel& channel) {
  mMaster.add(channel);
}

/**
 * @brief Remove a channel
 * @param channel
 */
void Mixer::remove(Channel& channel) {
  mMaster.remove(channel);
}

/**
 * @brief Add an instrument
 * 
 * Add an instrument to the default master channel
 *
 * @param instrument
 */
void Mixer::add(Instrument& instrument) {
  mMaster.add(instrument);
}

/**
 * @brief Remove an instrument
 * 
 * Remove an instrument that was added to the default master channel
 * 
 * @param instrument
 */
void Mixer::remove(Instrument& instrument) {
  mMaster.remove(instrument);
}

/**
 * @brief Add an effect
 * 
 * Add an effect to the default master channel
 *
 * @param effect
 */
void Mixer::add(Effect& effect) {
  mMaster.add(effect);
}


/**
 * @brief Remove an effect
 * 
 * Remove an effect that was added to the default master channel
 * 
 * @param effect
 */
void Mixer::remove(Effect& effect) {
  mMaster.remove(effect);
}


}
