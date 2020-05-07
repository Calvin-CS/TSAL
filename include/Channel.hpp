#ifndef CHANNEL_H
#define CHANNEL_H

#include "EffectChain.hpp"
#include "Instrument.hpp"
#include "OutputDevice.hpp"
#include "ParameterManager.hpp"
#include "Amp.hpp"
#include "Panning.hpp"

namespace tsal {

/** @class Channel
 * @brief Routes instruments and other channels through an effect chain and to the master channel
 * on the mixer
 * 
 * Instruments, effects, and channels can all be added to a channel. The mixer has one default master channel
 * but more channels can be added to the mixer to increase flexibility
 */
class Channel : public ChannelDevice, public ParameterManager {
  public:
    Channel();
    virtual ~Channel();
    static std::vector<Parameter> ChannelParameters;
    enum Parameters {
                     VOLUME = 0,
                     PANNING,
    };
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    virtual void updateContext(const Context& context) override;
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

  protected:
    virtual void parameterUpdate(unsigned int id) override;
  private:
    Amp mAmp;
    Panning mPanning;
    RouteDevice<OutputDevice> mChannelIn;
    RouteDevice<Instrument> mRoutedInstruments;
    RouteDevice<Channel> mRoutedChannels;
    EffectChain mEffectChain;
};

}

#endif
