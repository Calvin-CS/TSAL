#include <iostream>

#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

namespace tsal {

/** @class OutputDevice
 * @brief Base class for a device that produces output
 * 
 */
class OutputDevice {
  public:
    virtual ~OutputDevice() {};
    /**
     * @brief Get the output for the device
     * 
     * @return double 
     */
    virtual double getOutput() { return 0.0; };
    /**
     * @brief Set the active status of the device
     * 
     * It is up to the class how to implement the active status
     * 
     * @param active 
     */
    virtual void setActive(bool active) { mActive = active; };
  protected:
    bool mActive = true;
};

};

#endif
