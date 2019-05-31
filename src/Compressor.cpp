#include "Compressor.h"
#include <cmath>
#include <iostream>

namespace tsal {

Compressor::Compressor() {
  setAttackTime(1.0);
  setReleaseTime(10.0);
  mBuffer = new double[mBufferFrames];
  mEnvelope = new double[mBufferFrames];
  // Set this so that the next buffer sample is immediately calculated
  mCurrentSample = mBufferFrames;
}

// This may not be the best implementation, maybe a circular buffer would work better, but 
// it seems to be fine
double Compressor::nextBufferSample() {
  // If the end of the buffer has been reached, more audio samples need to be generated
  if (mCurrentSample == mBufferFrames) {
    mCurrentSample = 0;
    // Generate new audio data
    for (unsigned i = 0; i < mBufferFrames; i++) {
      mBuffer[i] = getNodeSamples();
    }
    // Filter the generated audio data
    filterAudio();
  }

  // Get an audio sample
  return mBuffer[mCurrentSample++];
}

void Compressor::getEnvelope() {
  for (unsigned i = 0; i < mBufferFrames; i++) {
    // Using peak detection since it is faster
    // Maybe implement RMS
    double envIn = std::abs(mBuffer[i]);

    double gain = mEnvelopeSample < envIn ? mAttackGain : mReleaseGain;
    mEnvelopeSample = envIn + gain * (mEnvelopeSample - envIn);

    mEnvelope[i] = mEnvelopeSample;
  }
}

void Compressor::filterAudio() {
  double postGainAmp = dbToAmp(mPostGain);

  // If there is any pregain, apply it to the audio buffer
  if (mPreGain != 0.0) {
    double preGainAmp = dbToAmp(mPreGain);
    for (unsigned i = 0; i < mBufferFrames; i++) {
      mBuffer[i] *= preGainAmp;
    }
  }

  getEnvelope();
  calculateSlope();
  
  // Apply the adjusted gain and postGain to the audio buffer
  for (unsigned i = 0; i < mBufferFrames; i++) {
    mGain = mSlope * (mThreshold - ampToDb(mEnvelope[i]));
    mGain = std::min(0.0, mGain);
    mGain = dbToAmp(mGain);
    mBuffer[i] *= (mGain * postGainAmp);
  }
}

void Compressor::setAttackTime(double attackTime) {
  if (checkInRange(attackTime, mAttackTimeRange)) {
    std::cout << "AttackTime: invalid range" << std::endl;
    return;
  }
  mAttackTime = attackTime/1000;
  mAttackGain = std::exp(-1.0 / (mSampleRate * mAttackTime));
}

void Compressor::setReleaseTime(double releaseTime) {
  mReleaseTime = releaseTime/1000;
  mReleaseGain = std::exp(-1.0 / (mSampleRate * mReleaseTime));
}

void Compressor::calculateSlope() {
  mSlope = 1.0 - (1.0 / mRatio);
}

double Compressor::ampToDb(double amplitude) {
  return 20.0 * std::log(amplitude) / M_LN10;
}

double Compressor::dbToAmp(double db) {
  return std::pow(10.0, db / 20.0);
}

bool Compressor::checkInRange(double parameter, range parameterRange) {
  return parameterRange.first < parameter && parameter > parameterRange.second;
}

range Compressor::mAttackTimeRange = std::make_pair(0.0, 1000.0);

}
