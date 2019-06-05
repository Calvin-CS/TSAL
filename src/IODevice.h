#include "InputDevice.h"
#include "OutputDevice.h"

#ifndef CHANNELDEVICE_H
#define CHANNELDEVICE_H

namespace tsal {

class ChannelDevice : public InputDevice, public OutputDevice {
  public:
    virtual double getOutput() override {
      return getInput();
    };
    void add(OutputDevice* output) {
      InputDevice::add(output);
    }
    void remove(OutputDevice* output) {
      InputDevice::remove(output);
    }
};

}
#endif
