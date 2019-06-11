#include "Effect.h"

#define COMPRESSOR_MAX_BUFFER 512

#ifndef COMPRESSOR_H
#define COMPRESSOR_H

// Using 512 as the buffer size for now, reimplement eventually

namespace tsal {

typedef std::pair<double, double> ParameterRange;

/** @class Compressor
 * @brief An audio compressor
 * 
 * A compressor used to reduce clipping. Essentially, if the sound routed through the 
 * compressor is louder than the compressors threshold, it will reduce the loudness.
 * Implementation adapted from https://christianfloisand.wordpress.com/2014/06/09/dynamics-processing-compressorlimiter-part-1/
 */
class Compressor : public Effect {
  public:
    Compressor();
    virtual double getOutput() override;
    void setAttackTime(double attackTime);
    void setReleaseTime(double releaseTime);
    void setThreshold(double threshold);
    void setRatio(double ratio);
    void setPreGain(double preGain);
    void setPostGain(double postGain);

    static double ampToDb(double amplitude);
    static double dbToAmp(double db);

  private:
    void filterAudio();
    void getEnvelope();
    void calculateSlope();
    double mEnvelopeSample;

    // Figure what an optimal buffer size would be 
    double mBuffer[COMPRESSOR_MAX_BUFFER];
    double mEnvelope[COMPRESSOR_MAX_BUFFER];
    unsigned mCurrentSample = COMPRESSOR_MAX_BUFFER;
      
    double mSlope;
    double mGain;
    double mAttackGain;
    double mReleaseGain;

    double mThreshold = 80.0;
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
