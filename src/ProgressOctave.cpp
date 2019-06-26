#include "ProgressOctave.hpp"

namespace tsal {

ProgressOctave::ProgressOctave(unsigned startNote, unsigned problemSize, unsigned numWorkers) {
  Oscillator* oscillatorPtr = nullptr;
  double startingFrequency = Oscillator::getFrequencyFromNote(startNote);
  // Thanks to human perception of frequency being logarithmic, an ocatve is simply
  // 2 * startingFrequency, so the difference in frequencies is startingFrequency
  double octavePortion = startingFrequency / numWorkers;
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
