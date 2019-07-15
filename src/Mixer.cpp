#include "Mixer.hpp"
#include "Channel.hpp"

namespace tsal {

void Mixer::errorCallback( RtAudioError::Type type, const std::string &errorText ) {
  // This example error handling function does exactly the same thing
  // as the embedded RtAudio::error() function.
  std::cout << "in errorCallback" << std::endl;
  if ( type == RtAudioError::WARNING )
    std::cerr << '\n' << errorText << "\n\n";
  else if ( type != RtAudioError::WARNING )
    throw( RtAudioError( errorText, type ) );
}

/* This is the main function that we give to the audio buffer to call for sampling
 * Depending on how it's configured, this will usually get called 44100 per second
 */
int Mixer::streamCallback(void *outputBuffer,
                   __attribute__((unused)) void *inputBuffer,
                   unsigned nBufferFrames, 
                   __attribute__((unused)) double streamTime,
                   RtAudioStreamStatus status,
                   void *data) {
  
  BIT_DEPTH *buffer = (BIT_DEPTH *) outputBuffer;
  Mixer *audio = (Mixer *) data;

  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;

  for (unsigned i = 0; i < nBufferFrames; i++) {
    *buffer++ = (BIT_DEPTH) audio->getInput();
  }

  return 0;        
}

void Mixer::initalizeStream() {
  if (mRtAudio.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(1);
  }
  
  unsigned deviceId = mRtAudio.getDefaultOutputDevice(); 
  RtAudio::DeviceInfo info = mRtAudio.getDeviceInfo(deviceId);
  // If the sample rate hasn't been set, use the highest sample rate supported
    std::cout << "TEST2" << mSampleRate << std::endl;
  if (mSampleRate == 0) {
    mSampleRate = info.sampleRates[info.sampleRates.size() - 1];
    std::cout << "TEST" << mSampleRate << std::endl;
  }
  
  mRtAudio.showWarnings(true);

  mBufferFrames = 512;
  RtAudio::StreamParameters oParams;
  oParams.deviceId = deviceId;
  oParams.nChannels = mChannels;
  oParams.firstChannel = 0;

  RtAudio::StreamOptions options;
  // Investigate what exactly these flags do
  //options.flags = RTAUDIO_HOG_DEVICE | RTAUDIO_SCHEDULE_REALTIME;
  
  std::cout << "Sample rate: " << mSampleRate 
            << "\nBuffer frames: " << mBufferFrames
            << std::endl;

  mSequencer.setBPM(60);
  mSequencer.setPPQ(240);

  // Add a compressor so people don't break their sound cards
  mMaster.setMixer(this);
  mCompressor.setMixer(this);
  mMaster.add(mCompressor);

  try {
    mRtAudio.openStream(&oParams, NULL, FORMAT, mSampleRate, &mBufferFrames, 
      &streamCallback, (void *)this, &options, &errorCallback);
    mRtAudio.startStream();
  } catch (RtAudioError& e) {
    e.printMessage();
  } 
}

Mixer::Mixer() {
  mChannels = 1;
  initalizeStream();
}

/**
 * @brief Construct a new Mixer
 * 
 * @param sampleRate if left blank, TSAudio will default to the highest sample rate supported
 */
Mixer::Mixer(unsigned sampleRate) {
  mSampleRate = sampleRate;
  // Eventually it would be nice to play in stereo, but that sounds hard for now
  mChannels = 1;
  initalizeStream();
}

Mixer::~Mixer() {
  if (mRtAudio.isStreamOpen())
    mRtAudio.closeStream();
}

double Mixer::getInput() {
  mSequencer.tick();
  mCurrentTick = mSequencer.getTick();
  return mMaster.getOutput();
}

/**
 * @brief Add a channel 
 *
 * @param channel
 */
void Mixer::add(Channel& channel) {
  mMaster.add(channel);
  channel.setMixer(this);
}

/**
 * @brief Remove a channel
 * @param channel
 */
void Mixer::remove(Channel& channel) {
  mMaster.remove(channel);
  channel.setMixer(nullptr);
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
  instrument.setSequencer(&mSequencer);
  instrument.setMixer(this);
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
  instrument.setSequencer(nullptr);
  instrument.setMixer(nullptr);
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
  effect.setMixer(this);
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
  effect.setMixer(nullptr);
}

unsigned OutputDevice::getSampleRate() const {
  // the default sample rate is to prevent the instrument from breaking until
  // It is added to an actual mixer. Since it won't be sampled until it's added
  // to a mixer, the value of the default sample rate doesn't really matter
  return (mMixer == nullptr) ? 44100 : mMixer->getSampleRate();
}

}
