#ifndef CHANNEL_H
#define CHANNEL_H

#include "EffectChain.hpp"
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
class Channel : public ChannelDevice {
  public:
    Channel(Mixer* mixer);
    virtual ~Channel();
    virtual void getOutput(std::vector<float>& buffer, unsigned long frameCount, unsigned channelCount) override;
    virtual void setMixer(Mixer* mixer) override;
    virtual void setParentChannel(Channel* channel) override;
    void add(Channel& channel);
    void add(Effect& effect, unsigned position);
    void add(Effect& effect);
    void add(Instrument& instrument);

    void remove(Effect& effect);
    void remove(Channel& channel);
    void remove(Instrument& instrument);

    int getChannelCount() { return mRoutedChannels.size(); };
    int getInstrumentCount() { return mRoutedInstruments.size(); };
    int getEffectCount() { return mEffectChain.size(); };

  private:
    RouteDevice<OutputDevice> mChannelIn;
    RouteDevice<Instrument> mRoutedInstruments;
    RouteDevice<Channel> mRoutedChannels;
    EffectChain mEffectChain;
};

}

#endif
