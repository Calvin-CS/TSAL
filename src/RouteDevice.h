#include "InputDevice.h"
#include "OutputDevice.h"

#ifndef ROUTEDEVICE_H
#define ROUTEDEVICE_H

namespace tsal {

class RouteDevice : public InputDevice, public OutputDevice {
  public:
    virtual double getInput() override;
    virtual double getOutput() override {
      return getInput();
    };
    void add(OutputDevice* output);
    void remove(OutputDevice* output);
  protected:
    std::vector<OutputDevice*> mOutputDevices;

};

}
#endif
