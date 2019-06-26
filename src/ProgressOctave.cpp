#include "ProgressOctave.hpp"

namespace tsal {

ProgressOctave::ProgressOctave(unsigned startNote, unsigned problemSize, unsigned numWorkers) {
  Oscillator* oscillatorPtr = nullptr;
  double startingFrequency = Oscillator::getFrequencyFromNote(startNote);
  // Jump by 2 octaves 4 * startingFrequency - startingFrequency
  double octavePortion = (4 * startingFrequency - startingFrequency) / numWorkers;
  mStepValue = octavePortion / problemSize;
  for (unsigned i = 0; i < numWorkers; i++) {
    oscillatorPtr = new Oscillator();
    oscillatorPtr->setGain(0.05);
    oscillatorPtr->setFrequency(startingFrequency + octavePortion * i);
    mOscillators.add(*oscillatorPtr);
  }
}

double ProgressOctave::getOutput() {
  return mOscillators.getOutput();
}

void ProgressOctave::update(unsigned id) {
  mOscillators[id].setFrequency(mOscillators[id].getFrequency() + mStepValue);
}

}
