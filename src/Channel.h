#include "Effect.h"
#include "IODevice.h"
#include "Instrument.h"

#ifndef CHANNEL_H
#define CHANNEL_H


namespace tsal {

class Channel : public ChannelDevice {
  public:
    Channel();
    void add(Channel* channel);
    void remove(Channel* channel);
    void add(Effect* effect);
    void remove(Effect* effect);
    void add(Instrument* instrument);
    void remove(Instrument* instrument);
  private:
    ChannelDevice mChannelIn;
    Effect* mEffectChain = nullptr;
};

};

#endif
