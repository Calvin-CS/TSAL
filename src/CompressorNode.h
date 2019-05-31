
#include "AudioNode.h"

#ifndef COMPRESSORNODE_H
#define COMPRESSORNODE_H

// Using 512 as the buffer size for now, reimplement eventually

namespace tsal {

typedef std::pair<double, double> range;

/** @class CompressorNode
 * @brief A DSP compressor
 * 
 * A compressor used to reduce clipping. Essentially, if the sound routed through the 
 * compressor is louder than the compressors threshold, it will reduce the loudness.
 * Implementation adapted from https://christianfloisand.wordpress.com/2014/06/09/dynamics-processing-compressorlimiter-part-1/
 */
class CompressorNode : public AudioNode {
  public:
    CompressorNode();
    virtual double nextBufferSample() override;

    /**
     * @brief Set the attack time (milliseconds)
     * 
     * @param attackTime
     */
    void setAttackTime(double attackTime);

    /**
     * @brief Set the release time (milliseconds)
     * 
     * @param releaseTime 
     */
    void setReleaseTime(double releaseTime);

    static double ampToDb(double amplitude);
    static double dbToAmp(double db);

  private:
    /**
     * @brief Compress the audio in the buffer if necessary
     * 
     */
    void filterAudio();

    /**
     * @brief Get the sound envelope for the sample buffer
     * 
     */
    void getEnvelope();

    /**
     * 
     * @brief Get the slope based off the ratio
     * 
     */
    void calculateSlope();

    double mEnvelopeSample;

    // These values should be configurable
    double* mBuffer;
    double* mEnvelope;
    unsigned mCurrentSample;
    
    double mSlope;
    double mGain;
    double mAttackGain;
    double mReleaseGain;

    double mThreshold = 70.0;
    double mRatio = 2.0;
    double mPreGain = 0.0;
    double mPostGain = 0.0;
    double mAttackTime = 1.0;
    double mReleaseTime = 500.0;

    static bool checkInRange(double parameter, range parameterRange);
    static range mAttackTimeRange;
};

}
#endif
