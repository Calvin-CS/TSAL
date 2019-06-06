#include "OutputDevice.h"
#include <vector>

#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

namespace tsal {

/** @class InputDevice
 * @brief Base class for a device that takes input
 * 
 */
class InputDevice {
  public:
    virtual ~InputDevice() {};
    virtual double getInput();
  protected:
    void add(OutputDevice* output);
    void remove(OutputDevice* output);
    std::vector<OutputDevice*> mOutputDevices;
};

};

#endif
  
