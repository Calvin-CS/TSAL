#include "PolySynth.hpp"

namespace tsal {

PolySynth::PolySynth() {
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

void PolySynth::noteOn(unsigned note, double velocity) {
  Synth* voice = getInactiveVoice();
  if (voice == nullptr) {
    // Maybe change the behavior to grab the nearest note 
    return;
  }
  voice->noteOn(note, velocity);
}

void PolySynth::noteOff(unsigned note) {
  for (unsigned i = 0; i < NUM_VOICES; i++) {
    std::cout << mVoices[i].getNote() << " " << note << std::endl;
    if (mVoices[i].getNote() == note) {
      std::cout << "Note Off" << std::endl;
      mVoices[i].noteOff();
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
