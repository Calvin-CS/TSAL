#include "Mixer.hpp"
#include "Util.hpp"
#include <cmath>

#ifndef ENVELOPE_H
#define ENVELOPE_H

#define MIN_VALUE 0.0001

namespace tsal {

/** @class Envelope
 * @brief An sound envelope that can be used to change a sound over time
 * 
 * A 4 stage envelope transitions from attack, to decay, to sustain, and then to release. It achieves
 * a smoother sound when overlayed on an instrument
 * Implementation adapted from http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
 */
class Envelope {
  public:
    enum EnvelopeState {
      OFF,
      ATTACK,
      DECAY,
      SUSTAIN,
      RELEASE
    };
    Envelope();
    double getEnvelope();
    void updateState();
    void start();
    void stop();
    void setAttackTime(double attackTime);
    void setDecayTime(double decayTime);
    void setSustainLevel(double level);
    void setReleaseTime(double releaseTime);

    double getStateValue(EnvelopeState state) { return mStateValue[state]; };
    // Min value exists since the calculateMultiplier function doesn't work with 0
  private:
    void calculateMultiplier(double startLevel, double endLevel, unsigned lengthInSamples);
    bool stateIsTimed();
    EnvelopeState mState = OFF; 
    double mStateValue[5];
    unsigned mCurrentStateIndex = 0;
    unsigned mNextStateIndex = 0;
    double mEnvelopeValue = 0.0;
    double mMultiplier = 0.0;

    static ParameterRange<double> mTimeRange;
    static ParameterRange<double> mSustainRange;
};

}

#endif
