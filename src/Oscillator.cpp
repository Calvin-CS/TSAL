#include "Oscillator.h"
#include <iostream>

#define SCALE 32767.0

Oscillator::Oscillator(unsigned sampleRate) {
  mSampleRate = sampleRate;
  setMode(SINE);
  setGain(0.3);
  setFrequency(440);
}

void Oscillator::start() {
  mActive = true;
}

void Oscillator::stop() {
  mActive = false;
}

void Oscillator::setWaveform(std::unique_ptr<Waveform> waveform) {
  mCustomWaveform = std::move(waveform);
  setMode(CUSTOM);
}

void Oscillator::setNote(unsigned note) {
  setFrequency(getFrequencyFromNote(note));
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
  if (!mActive) {
    return 0;
  }

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

unsigned Oscillator::getNoteFromFrequency(double frequency) {
  return (12/log(2)) * log(frequency/27.5) + 21;
}

double Oscillator::getFrequencyFromNote(unsigned note) {
  return 27.5 * pow(2.0, (note - 21) / 12.0);
};
