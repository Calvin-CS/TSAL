#include "OutputDevice.h"
#include <vector>

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

namespace tsal {
  
class InputDevice {
  public:
    virtual double getInput();
    void add(OutputDevice* output);
  protected:
    std::vector<OutputDevice*> mOutputDevices;
};

};

#endif
  
