#include "PolySynth.hpp"

namespace tsal {

PolySynth::PolySynth(Mixer* mixer) : Instrument(mixer), mVoices(20, Synth(mixer)) {
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    mVoices[i].setActive(false);
    mVoices[i].setVolume(0.3);
  }
}

double PolySynth::getOutput() {
  double output = 0.0;
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    output += mVoices[i].getOutput();
  }
  return output;
}

void PolySynth::play(double note, double velocity) {
  Synth* voice = getInactiveVoice();
  if (voice == nullptr) {
    // Maybe change the behavior to grab the nearest note 
    return;
  }
  voice->play(note, velocity);
}

void PolySynth::stop(double note) {
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    if (mVoices[i].getNote() == note) {
      mVoices[i].stop();
      mVoices[i].setActive(false);
    }
  }
}

void PolySynth::setMode(Oscillator::OscillatorMode mode) {
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    mVoices[i].setMode(mode);
  }
}

Synth* PolySynth::getInactiveVoice() {
  Synth* voice = nullptr;
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    if (!mVoices[i].isActive()) {
      voice = &mVoices[i];
      voice->setActive();
      break;
    }
  }
  return voice;
}

}
