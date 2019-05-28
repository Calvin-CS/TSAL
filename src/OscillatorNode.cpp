#include "OscillatorNode.h"
#include <iostream>

#define SCALE 32767.0

OscillatorNode::OscillatorNode(unsigned sampleRate) {
  mSampleRate = sampleRate;
  setMode(SINE);
  setGain(0.3);
  setFrequency(440);
}

void OscillatorNode::start() {
  mActive = true;
}

void OscillatorNode::stop() {
  mActive = false;
}

void OscillatorNode::setWaveform(std::unique_ptr<Waveform> waveform) {
  mCustomWaveform = std::move(waveform);
  setMode(CUSTOM);
}

void OscillatorNode::setNote(unsigned note) {
  setFrequency(getFrequencyFromNote(note));
}

void OscillatorNode::setFrequency(double frequency) {
  mFrequency = frequency;
  mPhaseStep = mFrequency * 2 * M_PI / mSampleRate;
}

void OscillatorNode::setGain(double gain) {
  mGain = 0.5 * gain;
}

void OscillatorNode::setMode(OscillatorMode mode) {
  mMode = mode;
}

double OscillatorNode::getBufferSample() {
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

unsigned OscillatorNode::getNoteFromFrequency(double frequency) {
  return (12/log(2)) * log(frequency/27.5) + 21;
}

double OscillatorNode::getFrequencyFromNote(unsigned note) {
  return 27.5 * pow(2.0, (note - 21) / 12.0);
};
