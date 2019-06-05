#include "TSAudio.h"

namespace tsal {

void errorCallback( RtAudioError::Type type, const std::string &errorText ) {
  // This example error handling function does exactly the same thing
  // as the embedded RtAudio::error() function.
  std::cout << "in errorCallback" << std::endl;
  if ( type == RtAudioError::WARNING )
    std::cerr << '\n' << errorText << "\n\n";
  else if ( type != RtAudioError::WARNING )
    throw( RtAudioError( errorText, type ) );
}

int streamCallback(void *outputBuffer, void *inputBuffer, unsigned nBufferFrames, 
  double streamTime, RtAudioStreamStatus status, void *data) {
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
  if (mSampleRate == 0) {
    mSampleRate = info.sampleRates[info.sampleRates.size() - 1];
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

  try {
    mRtAudio.openStream(&oParams, NULL, FORMAT, mSampleRate, &mBufferFrames, 
      &streamCallback, (void *)this, &options, &errorCallback);
    mRtAudio.startStream();
  } catch (RtAudioError& e) {
    e.printMessage();
  }

  // Add a compressor so people don't break their sound cards
}

Mixer::Mixer() {
  mChannels = 1;
  initalizeStream();
}

Mixer::Mixer(unsigned sampleRate) {
  mSampleRate = sampleRate;
  mChannels = 1;
  initalizeStream();
}

Mixer::~Mixer() {
  if (mRtAudio.isStreamOpen())
    mRtAudio.closeStream();
}

void Mixer::add(Channel* channel) {
  InputDevice::add(channel);
}
}
