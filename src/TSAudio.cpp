#include "TSAudio.h"

namespace tsal {

typedef signed short MY_TYPE;

void errorCallback( RtAudioError::Type type, const std::string &errorText )
{
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
  MY_TYPE *buffer = (MY_TYPE *) outputBuffer;
  TSAudio *audio = (TSAudio *) data;

  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;

  for (unsigned i = 0; i < nBufferFrames; i++) {
    *buffer++ = (MY_TYPE) audio->getNodeSamples();
  }
  
  return 0;        
}

void TSAudio::initalizeStream() {
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

  std::cout << "Using sample rate: " << mSampleRate << std::endl;
  
  mRtAudio.showWarnings(true);

  unsigned bufferFrames = 512;
  RtAudio::StreamParameters oParams;
  oParams.deviceId = deviceId;
  oParams.nChannels = mChannels;
  oParams.firstChannel = 0;

  RtAudio::StreamOptions options;
  // Investigate what exactly these flags do
  //options.flags = RTAUDIO_HOG_DEVICE | RTAUDIO_SCHEDULE_REALTIME;
  
  try {
    mRtAudio.openStream(&oParams, NULL, RTAUDIO_SINT16, mSampleRate, &bufferFrames, 
      &streamCallback, (void *)this, &options, &errorCallback);
    mRtAudio.startStream();
  } catch (RtAudioError& e) {
    e.printMessage();
  }
}

TSAudio::TSAudio() {
  mChannels = 1;
  initalizeStream();
}

TSAudio::TSAudio(unsigned channels, unsigned sampleRate) {
  mSampleRate = sampleRate;
  mChannels = channels;
  initalizeStream();
}

TSAudio::~TSAudio() {
  if (mRtAudio.isStreamOpen())
    mRtAudio.closeStream();
}

}
