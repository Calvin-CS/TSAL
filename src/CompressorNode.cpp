#include "CompressorNode.h"
#include <math.h>

CompressorNode::CompressorNode(unsigned sampleRate) {
  mSampleRate = sampleRate;
}

double CompressorNode::nextBufferSample() {
  if (mCurrentSample < mAudioDataSize) {
    
  }
}

void CompressorNode::getEnvelope() {
  double attackGain = std::exp(-1.0 / mSampleRate * 10.0);
  double releaseGain = std::exp(-1.0 / mSampleRate * 10.0);

  for (unsigned i = 0; i < 512; i++) {
    // Using peak detection
    // Maybe implement RMS
    double envIn = std::abs(mAudioBuffer[i]);

    double gain = mEnvelopeSample < envIn ? attackGain : releaseGain;
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

void CompressorNode::calculateSlope() {
  mSlope = 1.0 - (1.0/mRatio);
}

double CompressorNode::ampToDb(double amplitude) {
   20 * std::log(amplitude) / M_LN10;
}

double CompressorNode::dbToAmp(double db) {
  return std::pow(10, db / 20);
}
