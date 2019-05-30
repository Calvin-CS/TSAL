#include "CompressorNode.h"
#include <math.h>
#include <iostream>

CompressorNode::CompressorNode() {
  setAttackTime(0.01);
  setReleaseTime(10.0);
}

double CompressorNode::nextBufferSample() {
  
  // We have reached the end of the buffer
  if (mCurrentSample == mAudioDataSize) {
    mCurrentSample = 0;
    for (unsigned i = 0; i < mAudioDataSize; i++) {
      mAudioBuffer[i] = getNodeSamples();
    }
    filterAudio();
  }
  return mAudioBuffer[mCurrentSample++];
  
  //return getNodeSamples();
}

void CompressorNode::getEnvelope() {
  // double attackGain = std::exp(-1.0 / (mSampleRate * mAttackTime));
  // double releaseGain = std::exp(-1.0 / (mSampleRate * mReleaseTime));/

  for (unsigned i = 0; i < mAudioDataSize; i++) {
    // Using peak detection since it is faster
    // Maybe implement RMS
    double envIn = std::abs(mAudioBuffer[i]);

    double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
    mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);

    mEnvelope[i] = mEnvelopeSample;
  }
}

void CompressorNode::filterAudio() {
  double postGainAmp = dbToAmp(mPostGain);

  if (mPreGain != 0.0) {
    double preGainAmp = dbToAmp(mPreGain);
    for (unsigned i = 0; i < mAudioDataSize; i++) {
      mAudioBuffer[i] *= preGainAmp;
    }
  }

  getEnvelope();
  calculateSlope();
  
  for (unsigned i = 0; i < mAudioDataSize; i++) {
    mGain = mSlope * (mThreshold - ampToDb(mEnvelope[i]));
    mGain = std::min(0.0, mGain);
    mGain = dbToAmp(mGain);
    mAudioBuffer[i] *= (mGain * postGainAmp);
  }
}

void CompressorNode::setAttackTime(double attackTime) {
  mAttackTime = attackTime;
  mAttackGain = std::exp(-1.0 / (mSampleRate * attackTime));
}

void CompressorNode::setReleaseTime(double releaseTime) {
  mReleaseTime = releaseTime;
  mReleaseGain = std::exp(-1.0 / (mSampleRate * releaseTime));
}

void CompressorNode::calculateSlope() {
  mSlope = 1.0 - (1.0 / mRatio);
}

double CompressorNode::ampToDb(double amplitude) {
  return 20.0 * std::log(amplitude) / M_LN10;
}

double CompressorNode::dbToAmp(double db) {
  return std::pow(10.0, db / 20.0);
}
