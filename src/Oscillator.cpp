#include "Oscillator.h"
#include <iostream>

#define SCALE 32767.0
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
  Oscillator *audio = (Oscillator *) data;

  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;

  for (unsigned i = 0; i < nBufferFrames; i++) {
    *buffer++ = (MY_TYPE) audio->getBufferSample();
  }

  return 0;        
}

Oscillator::Oscillator() {
  mSampleRate = 96000;
  mChannels = 1;
  mGain = 0.5;
  mMode = SINE;
  setFrequency(440);
  initStream();
  
}

Oscillator::Oscillator(unsigned channels, unsigned sampleRate) {
  mSampleRate = sampleRate;
  mChannels = channels;
  mGain = 0.5;
  mMode = SINE;
  setFrequency(440);
  initStream();
}

void Oscillator::initStream() {
  if (mRtAudio.getDeviceCount() < 1) {
    std::cout << "\nNo audio devices found!\n";
    exit(1);
  }

  mRtAudio.showWarnings(true);

  unsigned bufferFrames = 512;
  RtAudio::StreamParameters oParams;
  oParams.deviceId = mRtAudio.getDefaultOutputDevice();
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

Oscillator::~Oscillator() {
  if (mRtAudio.isStreamOpen())
    mRtAudio.closeStream();
}

void Oscillator::setWaveform(std::unique_ptr<Waveform> waveform) {
  mCustomWaveform = std::move(waveform);
  setMode(CUSTOM);
}

void Oscillator::setNote(unsigned note) {
  setFrequency(27.5 * pow(2.0, (note - 21) / 12.0));
}

void Oscillator::setFrequency(double frequency) {
  mFrequency = frequency;
  mPhaseStep = mFrequency * 2 * M_PI / mSampleRate;
}

void Oscillator::setGain(double gain) {
  mGain = 0.5 * gain;
}

void Oscillator::setMode(OscillatorMode mode) {
  mMode = mode;
}

double Oscillator::getBufferSample() {
  double value;
  switch (mMode) {
    case SINE:
      value = mSine.getWaveformSample(mPhase);
      break;
    case SAW:
      value = mSaw.getWaveformSample(mPhase);
      break;
    case SQUARE:
      value = mSquare.getWaveformSample(mPhase);
      break;
    case CUSTOM:
      value = mCustomWaveform->getWaveformSample(mPhase);
      break;
  }

  mPhase += mPhaseStep;  
  if (mPhase >= 2 * M_PI)
    mPhase = 0;
  return value * SCALE * mGain;
}



