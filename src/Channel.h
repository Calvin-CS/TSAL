#include "Effect.h"
#include "IODevice.h"
#include "Instrument.h"

#ifndef CHANNEL_H
#define CHANNEL_H


namespace tsal {

class Channel : public OutputDevice {
  public:
    virtual double getOutput() override;
    void add(Effect* effect);
    void remove(Effect* effect);
    void add(Instrument* instrument);
    void remove(Instrument* instrument);
  private:
    IODevice mChannelIn;
    Effect* mEffectChain = nullptr;
};

};

#endif
