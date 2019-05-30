
#include "AudioNode.h"

#ifndef COMPRESSORNODE_H
#define COMPRESSORNODE_H

// Using 512 as the buffer size for now, reimplement eventually


/** \class CompressorNode
 * \brief an DSP compressor
 * 
 * A compressor used to reduce clipping 
 */
class CompressorNode : public AudioNode {
  public:
    CompressorNode(unsigned sampleRate);
    double nextBufferSample();
    void filterAudio();

    static double ampToDb(double amplitude);
    static double dbToAmp(double db);

  private:
    void getEnvelope();
    void calculateSlope();
    unsigned mSampleRate;
    double mEnvelopeSample;

    unsigned mAudioDataSize = 512;
    double mAudioBuffer[512];
    double mEnvelope[512];
    unsigned mCurrentSample = 511;
    
    double mSlope;
    double mGain;

    double mThreshold = 50.0;
    double mRatio = 2.0;
    double mKnee = 0.2;
    double mPreGain = 0.0;
    double mPostGain = 0.0;
    double mAttackTime = 10.0;
    double mReleaseTime = 50.0;
    double mLookAheadTime = 0.0;
};

#endif
