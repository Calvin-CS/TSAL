#include "Compressor.hpp"
#include "Mixer.hpp"
#include "Util.hpp"
#include <iostream>
  
namespace tsal {

Compressor::Compressor(Mixer* mixer) : Effect(mixer), mBuffer(COMPRESSOR_MAX_BUFFER), mEnvelope(COMPRESSOR_MAX_BUFFER) {
};

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

void Compressor::setMixer(Mixer *mixer) {
  OutputDevice::setMixer(mixer);
  setAttackTime(1.0);
  setReleaseTime(1500.0);
}

/**
 * @brief Get the sound envelope for the sample buffer
 * 
 */
void Compressor::getEnvelope(AudioBuffer<float> &buffer) {
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();
  for (unsigned i = 0; i < channels; i++) {
    for (unsigned long j = 0; j < frames; j++) {
      float envIn = std::abs(buffer[j * channels + i]);
      double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
      mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);
      if (i == 0) {
        mEnvelope[j] = mEnvelopeSample / channels;
      } else {
        mEnvelope[j] += mEnvelopeSample / channels;
      }
    }
  }
         
  // for (unsigned i = 0; i < COMPRESSOR_MAX_BUFFER; i++) {
  //   // Peak detection
  //   double envIn = std::abs(mBuffer[i]);

  //   double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
      
  //   mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);

  //   mEnvelope[i] = mEnvelopeSample;
  // }
}
/**
 * @brief Compress the audio in the buffer if necessary
 * 
 */
void Compressor::filterAudio(AudioBuffer<float> &buffer) {
  double postGainAmp = Util::dbToAmp(mPostGain);

  // If there is any pregain, apply it to the audio buffer
  if (mPreGain != 0.0) {
    double preGainAmp = Util::dbToAmp(mPreGain);
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
    mGain = mSlope * (mThreshold - Util::ampToDb(mEnvelope[i]));
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
  mSlope = 1.0 - (1.0 / mRatio);
}

/**
 * @brief Set the attack time (ms)
 * 
 * @param attackTime
 */
void Compressor::setAttackTime(double attackTime) {
  attackTime = Util::checkParameterRange("Compressor: AttackTime", attackTime, mAttackTimeRange);
  mAttackGain = attackTime == 0.0 ? 0.0 : std::exp(-1.0 / (mMixer->getSampleRate() * attackTime/1000));
}

/**
 * @brief Set the release time (ms)
 * 
 * @param releaseTime 
 */
void Compressor::setReleaseTime(double releaseTime) {
  releaseTime = Util::checkParameterRange("Compressor: ReleaseTime", releaseTime, mReleaseTimeRange);
  mReleaseGain = releaseTime == 0.0 ? 0.0 : std::exp(-1.0 / (mMixer->getSampleRate() * releaseTime/1000));
}

/**
 * @brief Set the threshold
 * 
 * @param threshold (dB)
 */
void Compressor::setThreshold(double threshold) {
  mThreshold = Util::checkParameterRange("Compressor: Threshold", threshold, mThresholdRange);
}

/**
 * @brief Set the ratio
 * 
 * @param ratio (1: n)
 */
void Compressor::setRatio(double ratio) {
  mRatio = Util::checkParameterRange("Compressor: Ratio", ratio, mRatioRange); 
}

/**
 * @brief Set the pre gain
 * 
 * @param preGain (dB)
 */
void Compressor::setPreGain(double preGain) {
  mPreGain = Util::checkParameterRange("Compressor: PreGain", preGain, mGainRange);
}

/**
 * @brief Set the post gain
 * 
 * @param postGain (dB)
 */
void Compressor::setPostGain(double postGain) {
  mPostGain = Util::checkParameterRange("Compressor: PostGain", postGain, mGainRange);
}

Util::ParameterRange<double> Compressor::mAttackTimeRange = std::make_pair(0.0, 2000.0);
Util::ParameterRange<double> Compressor::mReleaseTimeRange = std::make_pair(0.0, 2000.0);
Util::ParameterRange<double> Compressor::mThresholdRange = std::make_pair(-60.0, 0.0);
Util::ParameterRange<double> Compressor::mRatioRange = std::make_pair(1.0, 20.0);
Util::ParameterRange<double> Compressor::mGainRange = std::make_pair(-30.0, 30.0);
}
