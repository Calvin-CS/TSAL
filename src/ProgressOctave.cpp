#include "ProgressOctave.hpp"

namespace tsal {

ProgressOctave::ProgressOctave(unsigned startNote, unsigned problemSize, unsigned numWorkers) {
  mStartNote = startNote;
  mProblemSize = problemSize;
  mNumWorkers = numWorkers;
}

void ProgressOctave::getOutput(AudioBuffer<float> &buffer) {
  mRoutedOscillators.getOutput(buffer);
}

void ProgressOctave::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  mRoutedOscillators.updateContext(context);
  
  double startingFrequency = Oscillator::getFrequencyFromNote(mStartNote);
  // Jump by 2 octaves, basically 3 * startingFrequency
  double octavePortion = (3 * startingFrequency) / mNumWorkers;
  mStepValue = octavePortion / mProblemSize;
  for (unsigned i = 0; i < mNumWorkers; i++) {
    mOscillators.push_back(std::make_unique<Oscillator>());

    auto& oscillator = mOscillators[i];
    mRoutedOscillators.add(*(oscillator.get()));
    oscillator->setFrequency(startingFrequency + octavePortion * i);
  }
}

/* @brief Update the oscillator that corresponds to the id
 *
 * @param id
 */
void ProgressOctave::update(unsigned id) {
  auto& oscillator = mOscillators[id];
  oscillator->setFrequency(oscillator->getFrequency() + mStepValue);
}

}
