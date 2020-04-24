#include "Delay.hpp"

namespace tsal {

std::vector<ParameterManager::Parameter> Delay::DelayParameters
({
  { .name="Delay", .min=0.0, .max=5.0, .defaultValue=1.0 },
  { .name="Feedback", .min=0.0, .max=1.0, .defaultValue=0.5 }
});

void Delay::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  // Update context dependent parameters 
  parameterUpdate(DELAY);
  mBuffer.setFrameCount(mDelayFrames);
  mBuffer.setChannelCount(mContext.getChannelCount());
}

void Delay::getOutput(AudioBuffer<float> &buffer) {
  if (!mActive) {
    return;
  }

  const auto channels = buffer.getChannelCount();
  for (unsigned long i = 0; i < buffer.getFrameCount(); i++) {
    int offset = mCounter - mDelayFrames;
    if (offset < 0) offset = mBuffer.size() + offset;

    for (unsigned j = 0; j < channels; j++) {
      const double output = mBuffer[offset];
      const double bufferValue = buffer[i * channels + j] + output * getParameter(FEEDBACK);
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
 * @param delay (seconds)
 */
void Delay::setDelay(double delay) {
  setParameter(DELAY, delay);
}

/**
 * @brief Set the feedback 
 * 
 * @param feedback 
 */
void Delay::setFeedback(double feedback) {
  setParameter(FEEDBACK, feedback);
}

void Delay::parameterUpdate(unsigned id) {
  switch(id) {
  case DELAY:
    mDelayFrames = std::round(getParameter(DELAY) * mContext.getSampleRate());
    break;
  }
}

}
