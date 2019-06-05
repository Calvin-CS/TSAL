#include "InputDevice.h"
#include "OutputDevice.h"
#include "IODevice.h"

#ifndef EFFECT_H
#define EFFECT_H

namespace tsal {

class Effect : public InputDevice, public OutputDevice {
  public:
    virtual double getInput() override;
    void add(ChannelDevice* channel);
    void add(Effect* effect);
  private:
    Effect* mNextEffect = nullptr;
    ChannelDevice* mChannelIn = nullptr;
};

};
#endif
