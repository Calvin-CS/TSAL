#include "Delay.hpp"
#include "Mixer.hpp"

namespace tsal {

Delay::Delay(Mixer* mixer) : Effect(mixer) {
  init();
}

void Delay::init() {
  mBuffer = std::make_unique<Buffer<double>>(mMixer->getSampleRate() * 2);
  Delay::mDelayRange = std::make_pair(0, mBuffer->size());
  setDelay(1000);
}

void Delay::setMixer(Mixer* mixer) {
  OutputDevice::setMixer(mixer);
  init();
}

double Delay::getOutput() {
  double const input = getInput();
  // We have to check if the buffer is null because Delay gets
  // added to the mixer master channel before the buffer is initialized
  // this is sort of a temporary fix until some better is figured out
  if (!mActive || mBuffer == nullptr) {
    return input;
  }

  auto& buffer = *mBuffer.get();
  int offset = mCounter - mDelay;

  // Clip lookback buffer-bound
  if (offset < 0)
    offset = buffer.size() + offset;

  double const output = buffer[offset];
  double const bufferValue = input + output * mFeedback;
  buffer[mCounter++] = bufferValue;

  // Clip delay counter
  if(mCounter >= buffer.size())
    mCounter -= buffer.size();

  return output + input;
}

/**
 * @brief Set the delay
 * 
 * @param delay (ms)
 */
void Delay::setDelay(unsigned delay) {
  delay = std::round(mMixer->getSampleRate() * ((double) delay / 1000));
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
