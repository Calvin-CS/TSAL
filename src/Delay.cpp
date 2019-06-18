#include "Delay.hpp"
#include "Mixer.hpp"

namespace tsal {
  
Delay::Delay() {
  mBuffer = std::make_unique<Buffer<double>>(Mixer::getSampleRate() * 2);
  Delay::mDelayRange = std::make_pair(0, mBuffer->size());
}

double Delay::getOutput() {
  if (!mActive) {
    return getInput();
  }

  auto& buffer = *mBuffer;
  int offset = mCounter - mDelay;

  // Clip lookback buffer-bound
  if (offset < 0)
    offset = buffer.size() + offset;

  double const output = buffer[offset];
  double const bufferValue = getInput() + output * mFeedback;
  buffer[mCounter++] = bufferValue;

  // Clip delay counter
  if(mCounter >= buffer.size())
    mCounter -= buffer.size();

  return output;
}

/**
 * @brief Set the delay
 * 
 * @param delay (ms)
 */
void Delay::setDelay(unsigned delay) {
  delay = std::round(Mixer::getSampleRate() * ((double) delay / 1000));
  mDelay = checkParameterRange("Delay: Delay", delay, mDelayRange);
}

/**
 * @brief Set the feedback 
 * 
 * @param feedback 
 */
void Delay::setFeedback(double feedback) {
  mFeedback = checkParameterRange("Delay: Feedback", feedback, mFeedbackRange);
}

ParameterRange<double> Delay::mFeedbackRange = std::make_pair(0.0, 1.0);
}
