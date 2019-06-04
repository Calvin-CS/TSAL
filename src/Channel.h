#include "Effect.h"
#include "Instrument.h"

#ifndef CHANNEL_H
#define CHANNEL_H

namespace tsal {

class Channel : public InputDevice, public OutputDevice {
  public:
    double getOutput();
    void add(Effect* effect);
    void remove(Effect* effect);
    void add(Instrument* instrument);
    void remove(Instrument* instrument);
  private:
    Effect* mEffectChain = nullptr;
};

};

#endif
