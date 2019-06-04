#include "InputDevice.h"
#include "OutputDevice.h"

#ifndef IODEVICE_H
#define IODEVICE_H

namespace tsal {

class IODevice : public InputDevice, public OutputDevice {
  public:
    virtual double getOutput() override {
      return getInput();
    };
};

}
#endif
