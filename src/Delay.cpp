#include "Delay.hpp"
#include "Mixer.hpp"

namespace tsal {

void Delay::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  mBuffer = std::make_unique<Buffer<double>>(getMixer()->getSampleRate() * 2);
  Delay::mDelayRange = std::make_pair(0, mBuffer->size());
  setDelay(1000);
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
  delay = std::round(getMixer()->getSampleRate() * ((double) delay / 1000));
  mDelay = Util::checkParameterRange("Delay: Delay", delay, mDelayRange);
}

/**
 * @brief Set the feedback 
 * 
 * @param feedback 
 */
void Delay::setFeedback(double feedback) {
  mFeedback = Util::checkParameterRange("Delay: Feedback", feedback, mFeedbackRange);
}

Util::ParameterRange<double> Delay::mFeedbackRange = std::make_pair(0.0, 1.0);
}
