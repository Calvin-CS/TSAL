#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Effect.hpp"
#include "Buffer.hpp"
#include "Util.hpp"
#include <vector>

/*
 * larger buffer = better quality but more latency
 * I just chose an arbitrary size
 */
#define COMPRESSOR_MAX_BUFFER 512

namespace tsal {

/** @class Compressor
 * @brief An audio compressor
 * 
 * A compressor used to reduce clipping. Essentially, if the sound routed through the 
 * compressor is louder than the compressors threshold, it will reduce the loudness.
 * Implementation adapted from https://christianfloisand.wordpress.com/2014/06/09/dynamics-processing-compressorlimiter-part-1/
 */
class Compressor : public Effect {
  public:
    Compressor(Mixer* mixer);
    virtual void getOutput(AudioBuffer<float>& buffer) override;
    virtual void setMixer(Mixer* mixer) override;
    void setAttackTime(double attackTime);
    void setReleaseTime(double releaseTime);
    void setThreshold(double threshold);
    void setRatio(double ratio);
    void setPreGain(double preGain);
    void setPostGain(double postGain);

  private:
    void filterAudio(AudioBuffer<float>& buffer);
    void getEnvelope(AudioBuffer<float>& buffer);
    void calculateSlope();
    double mEnvelopeSample = 0.0;

    Buffer<double> mBuffer;
    std::vector<float> mEnvelope;
    unsigned mCurrentSample = 0;
      
    double mSlope = 0.0;
    double mGain = 0.0;
    double mAttackGain = 0.0;
    double mReleaseGain = 0.0;

    double mThreshold = -30.0;
    double mRatio = 2.0;
    double mPreGain = 6.0;
    double mPostGain = 0.0;

    static Util::ParameterRange<double> mAttackTimeRange;
    static Util::ParameterRange<double> mReleaseTimeRange;
    static Util::ParameterRange<double> mThresholdRange;
    static Util::ParameterRange<double> mRatioRange;
    static Util::ParameterRange<double> mGainRange;
};

}
#endif
