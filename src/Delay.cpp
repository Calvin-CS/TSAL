#include "Delay.h"
#include "Mixer.h"

namespace tsal {
  
double Delay::getOutput() {
  if (!mActive) {
    return getInput();
  }

  int offset = mCounter - mDelay;

  // Clip lookback buffer-bound
  if (offset < 0)
    offset = DELAY_MAX_BUFFER + offset;

  double output = mBuffer[offset];
  double const bufferValue = getInput() + output * mFeedback;
  mBuffer[mCounter++] = bufferValue;

  // Clip delay counter
  if(mCounter >= DELAY_MAX_BUFFER)
    mCounter -= DELAY_MAX_BUFFER;

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

ParameterRange<unsigned> Delay::mDelayRange = std::make_pair(0, DELAY_MAX_BUFFER);
ParameterRange<double> Delay::mFeedbackRange = std::make_pair(0.0, 1.0);
}
