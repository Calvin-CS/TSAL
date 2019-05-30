
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
    CompressorNode();
    double nextBufferSample();
    void filterAudio();

    void setAttackTime(double attackTime);
    void setReleaseTime(double releaseTime);

    static double ampToDb(double amplitude);
    static double dbToAmp(double db);

  private:
    void getEnvelope();
    void calculateSlope();
    double mEnvelopeSample;

    unsigned mAudioDataSize = 512;
    double mAudioBuffer[512];
    double mEnvelope[512];
    unsigned mCurrentSample = 511;
    
    double mSlope;
    double mGain;
    double mAttackGain;
    double mReleaseGain;

    double mThreshold = 50.0;
    double mRatio = 2.0;
    double mKnee = 0.2;
    double mPreGain = 0.0;
    double mPostGain = 0.0;
    double mAttackTime = 1.0;
    double mReleaseTime = 50.0;
    double mLookAheadTime = 0.0;
};

#endif
