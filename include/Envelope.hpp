#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <algorithm>
#include "Mixer.hpp"
#include "OutputDevice.hpp"
#include "ParameterManager.hpp"
#include "Util.hpp"
#include <cmath>

namespace tsal {

/** @class Envelope
 * @brief An sound envelope that can be used to change a sound over time
 * 
 * A 4 stage envelope transitions from attack, to decay, to sustain, and then to release. It achieves
 * a smoother sound when overlayed on an instrument
 * Implementation adapted from http://www.martin-finke.de/blog/articles/audio-plugins-011-envelopes/
 */
class Envelope : public OutputDevice, public ParameterManager {
  public:
    Envelope() :
      ParameterManager({
                        { .name="Attack", .min=0.0, .max=2000.0, .defaultValue=0.01, .exclusiveMin=true },
                        { .name="Decay", .min=0.0, .max=2000.0, .defaultValue=0.5, .exclusiveMin=true},
                        { .name="Sustain", .min=0.0, .max=1.0, .defaultValue=0.5 },
                        { .name="Release", .min=0.0, .max=2000.0, .defaultValue=2.0, .exclusiveMin=true},
        })
    {
      setEnvelope(0.01, 0.5, 0.5, 2.0);
    };
    enum Parameters {
                     ATTACK,
                     DECAY,
                     SUSTAIN,
                     RELEASE,
    };
    double getSample();
    void updateState();
    void start();
    void stop();
    void setAttackTime(double attackTime);
    void setDecayTime(double decayTime);
    void setSustainLevel(double level);
    void setReleaseTime(double releaseTime);
    void setEnvelope(double attackTime, double decayTime, double sustainLevel, double releaseTime);
  protected:
    virtual void parameterUpdate(unsigned int id) override;
  private:
    enum EnvelopeState {
                        E_OFF,
                        E_ATTACK,
                        E_DECAY,
                        E_SUSTAIN,
                        E_RELEASE,
    };
    void calculateMultiplier(double startLevel, double endLevel, unsigned lengthInSamples);
    bool stateIsTimed();
    EnvelopeState mState = E_OFF; 
    double mStateValue[5] { 0.00001, 0.0, 0.0, 0.0, 0.0 };
    unsigned mCurrentStateIndex = 0;
    unsigned mNextStateIndex = 0;
    double mEnvelopeValue = 0.0;
    double mMultiplier = 0.0;

    static double TimeRangeMin;
    static Util::ParameterRange<double> mTimeRange;
    static Util::ParameterRange<double> mSustainRange;
};

}

#endif
