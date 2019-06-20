#ifndef CHANNEL_H
#define CHANNEL_H

#include "Effect.hpp"
#include "Instrument.hpp"
#include "OutputDevice.hpp"

namespace tsal {

/** @class Channel
 * @brief Routes instruments and other channels through an effect chain and to the master channel
 * on the mixer
 * 
 * Instruments, effects, and channels can all be added to a channel. The mixer has one default master channel
 * but more channels can be added to the mixer to increase flexibility
 */
class Channel : public OutputDevice {
  public:
    Channel();
    virtual double getOutput() override;
    void add(Channel& channel);
    void add(Effect& effect, unsigned position);
    void add(Effect& effect);
    void add(Instrument& instrument);

    void remove(Effect& effect);
    void remove(Channel& channel);
    void remove(Instrument& instrument);
  private:
    RouteDevice<OutputDevice> mChannelIn;
    RouteDevice<Instrument> mRoutedInstruments;
    RouteDevice<Channel> mRoutedChannels;
    Effect* mEffectChainEnd = nullptr;
};

};

#endif
