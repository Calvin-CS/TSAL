#include "Compressor.hpp"
#include "Mixer.hpp"
#include "Util.hpp"
#include <iostream>
  
namespace tsal {

Compressor::Compressor(Mixer* mixer) : Effect(mixer), mBuffer(COMPRESSOR_MAX_BUFFER), mEnvelope(COMPRESSOR_MAX_BUFFER) {
};

// This may not be the best implementation, maybe a circular buffer would work better, but 
// it seems to be fine
double Compressor::getOutput() {
  // If not active, just route the samples through without applying an filtering
  if (!mActive) {
    return getInput();
  }

  // Add a new sample into the buffer
  mBuffer[++mCurrentSample] = getInput();
  if (mCurrentSample >= COMPRESSOR_MAX_BUFFER) {
    mCurrentSample = 0;
    // Filter the generated audio data since the buffer is full
    filterAudio();
  }

  // Get an audio sample from the audio that has been processed in front
  return mBuffer[(mCurrentSample + 1) % COMPRESSOR_MAX_BUFFER];
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
void Compressor::getEnvelope() {
  for (unsigned i = 0; i < COMPRESSOR_MAX_BUFFER; i++) {
    // Peak detection
    double envIn = std::abs(mBuffer[i]);

    double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
    mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);

    mEnvelope[i] = mEnvelopeSample;
  }
}
/**
 * @brief Compress the audio in the buffer if necessary
 * 
 */
void Compressor::filterAudio() {
  double postGainAmp = Util::dbToAmp(mPostGain);

  // If there is any pregain, apply it to the audio buffer
  if (mPreGain != 0.0) {
    double preGainAmp = Util::dbToAmp(mPreGain);
    for (unsigned i = 0; i < COMPRESSOR_MAX_BUFFER; i++) {
      mBuffer[i] *= preGainAmp;
    }
  }

  getEnvelope();
  calculateSlope();
  
  // Apply the adjusted gain and postGain to the audio buffer
  for (unsigned i = 0; i < COMPRESSOR_MAX_BUFFER; i++) {
    mGain = mSlope * (mThreshold - Util::ampToDb(mEnvelope[i]));
    mGain = std::min(0.0, mGain);
    mGain = Util::dbToAmp(mGain);
    mBuffer[i] *= (mGain * postGainAmp);
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
