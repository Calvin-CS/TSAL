#include "InputDevice.h"
#include "OutputDevice.h"

#ifndef EFFECT_H
#define EFFECT_H

namespace tsal {

class Effect : public InputDevice, public OutputDevice {
  public:
    void add(Effect* effect);
    void remove(Effect* effect);
  private:
};

};
#endif
