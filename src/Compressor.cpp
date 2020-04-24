#include "Compressor.hpp"
#include "Util.hpp"
#include <iostream>
  
namespace tsal {

std::vector<ParameterManager::Parameter> Compressor::CompressorParameters
({
  { .name="Release", .min=0.0, .max=2000.0, .defaultValue=0.0 },
  { .name="Threshold", .min=-60.0, .max=60.0, .defaultValue=-30.0 },
  { .name="Ratio", .min=1.0, .max=20.0, .defaultValue=2.0 },
  { .name="Pre Gain", .min=-30.0, .max=30.0, .defaultValue=0.0 },
  { .name="Post Gain", .min=-30.0, .max=30.0, .defaultValue=0.0 },
});

void Compressor::getOutput(AudioBuffer<float> &buffer) {
  /* The Compressor uses a circular buffer where a value is written behind 
   * the value that was read. Once the buffer is full of new values, all
   * of the samples in the buffer are processed.
   */
  // If not active, just route the samples through without applying an filtering
  if (!mActive) {
    return; 
  }

  filterAudio(buffer);

  // Get an audio sample from the audio that has been processed in front
  // return mBuffer[mCurrentSample];
}

void Compressor::updateContext(const Context& context) {
  OutputDevice::updateContext(context);
  parameterUpdate(ATTACK);
  parameterUpdate(RELEASE);
}

/**
 * @brief Get the sound envelope for the sample buffer
 * 
 */
void Compressor::getEnvelope(AudioBuffer<float> &buffer) {
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();
  mEnvelope.resize(frames);
  for (unsigned i = 0; i < channels; i++) {
    for (unsigned long j = 0; j < frames; j++) {
      float envIn = std::abs(buffer[j * channels + i]);
      double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
      mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);
      if (i == 0) {
        mEnvelope[j] = mEnvelopeSample / (float) channels;
      } else {
        mEnvelope[j] += mEnvelopeSample / (float) channels;
      }
    }
  }
}
/**
 * @brief Compress the audio in the buffer if necessary
 * 
 */
void Compressor::filterAudio(AudioBuffer<float> &buffer) {
  double postGainAmp = Util::dbToAmp(getParameter(POST_GAIN));

  // If there is any pregain, apply it to the audio buffer
  if (getParameter(PRE_GAIN) != 0.0) {
    double preGainAmp = Util::dbToAmp(getParameter(PRE_GAIN));
    for (unsigned i = 0; i < buffer.size(); i++) {
      buffer[i] *= preGainAmp;
    }
  }

  getEnvelope(buffer);
  calculateSlope();
  
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();
  // Apply the adjusted gain and postGain to the audio buffer
  for (unsigned long i = 0; i < frames; i++) {
    mGain = mSlope * (getParameter(THRESHOLD) - Util::ampToDb(mEnvelope[i]));
    mGain = std::min(0.0, mGain);
    mGain = Util::dbToAmp(mGain);
    for (unsigned j = 0; j < channels; j++) {
      buffer[i * channels + j] *= (mGain * postGainAmp);
    }
  }
}
 
/**
 * 
 * @brief Get the slope based off the ratio
 * 
 */
void Compressor::calculateSlope() {
  mSlope = 1.0 - (1.0 / getParameter(RATIO));
}

/**
 * @brief Set the attack time (ms)
 * 
 * @param attackTime
 */
void Compressor::setAttackTime(double attackTime) {
  setParameter(ATTACK, attackTime);
}

/**
 * @brief Set the release time (ms)
 * 
 * @param releaseTime 
 */
void Compressor::setReleaseTime(double releaseTime) {
  setParameter(RELEASE, releaseTime);
}

/**
 * @brief Set the threshold
 * 
 * @param threshold (dB)
 */
void Compressor::setThreshold(double threshold) {
  setParameter(THRESHOLD, threshold);
}

/**
 * @brief Set the ratio
 * 
 * @param ratio (1: n)
 */
void Compressor::setRatio(double ratio) {
  setParameter(RATIO, ratio);
}

/**
 * @brief Set the pre gain
 * 
 * @param preGain (dB)
 */
void Compressor::setPreGain(double preGain) {
  setParameter(PRE_GAIN, preGain);
}

/**
 * @brief Set the post gain
 * 
 * @param postGain (dB)
 */
void Compressor::setPostGain(double postGain) {
  setParameter(POST_GAIN, postGain);
}

void Compressor::parameterUpdate(unsigned id) {
  switch(id) {
  case ATTACK:
    mAttackGain = getParameter(id) == 0.0 ? 0.0 : std::exp(-1.0 / (mContext.getSampleRate() * getParameter(id)/1000));
    break;
  case RELEASE:
    mReleaseGain = getParameter(id) == 0.0 ? 0.0 : std::exp(-1.0 / (mContext.getSampleRate() * getParameter(id)/1000));
    break;
  }
}

}
