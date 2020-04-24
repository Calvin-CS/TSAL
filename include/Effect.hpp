#ifndef EFFECT_H
#define EFFECT_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"
#include "RouteDevice.hpp"
#include "Instrument.hpp"
#include "ParameterManager.hpp"
#include <algorithm>

namespace tsal {

/** @class Effect
 * @brief An audio processing device that can be chained to a channel to produce audio effects 
 * on one or more instruments routed to the channel
 * 
 * An effect recieves input from the ChannelIn device or another effect in the chain.
 * It processes the audio and then continues to pass it up the chain until the audio reaches
 * the end and it routed to the mixer
 */
class Effect : public ChannelDevice, public ParameterManager {
  public:
    Effect() :
      ParameterManager(EffectParameters) {};
    Effect(std::vector<Parameter> parameters) :
      ParameterManager(EffectParameters) {
      addParameters(parameters);
    };
    ~Effect();
    enum Parameters {
                     WET_DRY = 0,
    };
    static std::vector<Parameter> EffectParameters;
    virtual void setParentChannel(Channel* channel) override;
};

}

#endif
