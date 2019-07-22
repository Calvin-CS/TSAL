#ifndef EFFECT_H
#define EFFECT_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"
#include "RouteDevice.hpp"
#include "Instrument.hpp"

namespace tsal {

/** @class Effect
 * @brief An audio processing device that can be chained to a channel to produce audio effects 
 * on one or more instruments routed to the channel
 * 
 * An effect recieves input from the ChannelIn device or another effect in the chain.
 * It processes the audio and then continues to pass it up the chain until the audio reaches
 * the end and it routed to the mixer
 */
class Effect : public InputDevice, public OutputDevice {
  public:
    ~Effect();
    virtual double getInput() override;
    void setInput(OutputDevice* input);

  private:
    OutputDevice* mInput = nullptr;
};

}

#endif
