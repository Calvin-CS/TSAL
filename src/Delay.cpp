#include "Delay.hpp"

namespace tsal {

Delay::Delay(const Context& context) : Effect(context), mBuffer(mContext.getSampleRate(), mContext.getChannelCount()){
}

/* @brief Dynamically allocates a buffer based on the sample rate
 *
 * Since the buffer since of the delay is dependent on the sample
 * rate, the buffer has to be reallocated whenever the sample rate
 * changes
 */
void Delay::init() {
  const unsigned delay = mContext.getSampleRate();
  mBuffer.setFrameCount(delay);
  Delay::mDelayRange = std::make_pair(0, delay);
  setDelay(1000);
}

void Delay::updateContext(const Context& context) {
  OutputDevice::updateContext(mContext);
  init();
}

void Delay::getOutput(AudioBuffer<float> &buffer) {
  if (!mActive) {
    return;
  }

  const auto channels = buffer.getChannelCount();
  for (unsigned long i = 0; i < buffer.getFrameCount(); i++) {
    int offset = mCounter - mDelay;
    if (offset < 0) offset = mBuffer.size() + offset;

    for (unsigned j = 0; j < channels; j++) {
      double const output = mBuffer[offset];
      double const bufferValue = buffer[i * channels + j] + output * mFeedback;
      mBuffer[mCounter++] = bufferValue;
      if (mCounter >= mBuffer.size()) {
        mCounter = 0;
      }
      buffer[i * channels + j] += output;
    }
  }
}

/**
 * @brief Set the delay
 * 
 * @param delay (ms)
 */
void Delay::setDelay(unsigned delay) {
  delay = std::round(mContext.getSampleRate() * ((double) delay / 1000));
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
