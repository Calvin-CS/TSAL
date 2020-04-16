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
      ParameterManager(std::vector<Parameter>(ParameterDefs, ParameterDefs + 4))
    {
      setEnvelope(0.0, 0.5, 0.5, 1.0);
    };
    static Parameter ParameterDefs[];
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
  private:
    enum EnvelopeState {
                        E_ATTACK,
                        E_DECAY,
                        E_SUSTAIN,
                        E_RELEASE,
                        E_OFF,
    };
    void calculateMultiplier(double startLevel, double endLevel, unsigned lengthInSamples);
    double getStateValue(EnvelopeState state); 
    bool stateIsTimed();
    EnvelopeState mState = E_OFF; 
    unsigned mCurrentStateIndex = 0;
    unsigned mNextStateIndex = 0;
    double mEnvelopeValue = 0.0;
    double mMultiplier = 0.0;
};

}

#endif
