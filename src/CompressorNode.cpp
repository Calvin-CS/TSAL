#include "CompressorNode.h"
#include <cmath>
#include <iostream>

namespace tsal {

CompressorNode::CompressorNode() {
  setAttackTime(1.0);
  setReleaseTime(10.0);
}

// This may not be the best implementation, maybe a circular buffer would work better, but 
// it seems to be fine
double CompressorNode::nextBufferSample() {
  // If the end of the buffer has been reached, more audio samples need to be generated
  if (mCurrentSample == mAudioDataSize) {
    mCurrentSample = 0;
    // Generate new audio data
    for (unsigned i = 0; i < mAudioDataSize; i++) {
      mBuffer[i] = getNodeSamples();
    }
    // Filter the generated audio data
    filterAudio();
  }

  // Get an audio sample
  return mBuffer[mCurrentSample++];
}

void CompressorNode::getEnvelope() {
  for (unsigned i = 0; i < mAudioDataSize; i++) {
    // Using peak detection since it is faster
    // Maybe implement RMS
    double envIn = std::abs(mBuffer[i]);

    double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
    mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);

    mEnvelope[i] = mEnvelopeSample;
  }
}

void CompressorNode::filterAudio() {
  double postGainAmp = dbToAmp(mPostGain);

  // If there is any pregain, apply it to the audio buffer
  if (mPreGain != 0.0) {
    double preGainAmp = dbToAmp(mPreGain);
    for (unsigned i = 0; i < mAudioDataSize; i++) {
      mBuffer[i] *= preGainAmp;
    }
  }

  getEnvelope();
  calculateSlope();
  
  // Apply the adjusted gain and postGain to the audio buffer
  for (unsigned i = 0; i < mAudioDataSize; i++) {
    mGain = mSlope * (mThreshold - ampToDb(mEnvelope[i]));
    mGain = std::min(0.0, mGain);
    mGain = dbToAmp(mGain);
    mBuffer[i] *= (mGain * postGainAmp);
  }
}

void CompressorNode::setAttackTime(double attackTime) {
  if (checkInRange(attackTime, mAttackTimeRange)) {
    std::cout << "AttackTime: invalid range" << std::endl;
    return;
  }
  mAttackTime = attackTime/1000;
  mAttackGain = std::exp(-1.0 / (mSampleRate * mAttackTime));
}

void CompressorNode::setReleaseTime(double releaseTime) {
  mReleaseTime = releaseTime/1000;
  mReleaseGain = std::exp(-1.0 / (mSampleRate * mReleaseTime));
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

bool CompressorNode::checkInRange(double parameter, range parameterRange) {
  return parameterRange.first < parameter && parameter > parameterRange.second;
}

range CompressorNode::mAttackTimeRange = std::make_pair(0.0, 1000.0);

}
