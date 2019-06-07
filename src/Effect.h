#include "InputDevice.h"
#include "OutputDevice.h"
#include "RouteDevice.h"
#include "Instrument.h"

#ifndef EFFECT_H
#define EFFECT_H

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
    virtual double getInput() override;
    void add(RouteDevice<OutputDevice> *channel) { mChannelIn = channel; };
    void removeChannel() { mChannelIn = nullptr; };
    void add(Effect* effect);
    void remove(Effect* effect);
    Effect* getNextEffect() { return mNextEffect; };
    void setNextEffect(Effect* effect) { mNextEffect = effect; };

  private:
    Effect* mNextEffect = nullptr;
    RouteDevice<OutputDevice>* mChannelIn = nullptr;
};

};
#endif
