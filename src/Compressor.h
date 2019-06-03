#include "AudioNode.h"

#define COMPRESSOR_MAX_BUFFER 512

#ifndef COMPRESSOR_H
#define COMPRESSOR_H

// Using 512 as the buffer size for now, reimplement eventually

namespace tsal {

typedef std::pair<double, double> ParameterRange;

/** @class Compressor
 * @brief A DSP compressor
 * 
 * A compressor used to reduce clipping. Essentially, if the sound routed through the 
 * compressor is louder than the compressors threshold, it will reduce the loudness.
 * Implementation adapted from https://christianfloisand.wordpress.com/2014/06/09/dynamics-processing-compressorlimiter-part-1/
 */
class Compressor : public AudioNode {
  public:
    Compressor();
    virtual double nextBufferSample() override;

    /**
     * @brief Set the attack time (ms)
     * 
     * @param attackTime
     */
    void setAttackTime(double attackTime);

    /**
     * @brief Set the release time (ms)
     * 
     * @param releaseTime 
     */
    void setReleaseTime(double releaseTime);

    /**
     * @brief Set the threshold
     * 
     * @param threshold (dB)
     */
    void setThreshold(double threshold);

    /**
     * @brief Set the ratio
     * 
     * @param ratio (1: n)
     */
    void setRatio(double ratio);

    /**
     * @brief Set the pre gain
     * 
     * @param preGain (dB)
     */
    void setPreGain(double preGain);
    
    /**
     * @brief Set the post gain
     * 
     * @param postGain (dB)
     */
    void setPostGain(double postGain);

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
    double mBuffer[COMPRESSOR_MAX_BUFFER];
    double mEnvelope[COMPRESSOR_MAX_BUFFER];
    unsigned mCurrentSample = COMPRESSOR_MAX_BUFFER;
      
    double mSlope;
    double mGain;
    double mAttackGain;
    double mReleaseGain;

    double mThreshold = 70.0;
    double mRatio = 2.0;
    double mPreGain = 0.0;
    double mPostGain = 0.0;

    static bool checkParameterRange(std::string name, double value, ParameterRange parameterRange);
    static ParameterRange mAttackTimeRange;
    static ParameterRange mReleaseTimeRange;
    static ParameterRange mThresholdRange;
    static ParameterRange mRatioRange;
    static ParameterRange mGainRange;
};

}
#endif
