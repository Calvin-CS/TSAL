#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include "Util.hpp"
#include <iostream>

typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0
#define PI2 (M_PI * 2)

namespace tsal {

/** @class OutputDevice
 * @brief Base class for a device that produces audio output
 * 
 */
class OutputDevice {
  public:
    virtual ~OutputDevice() {};

    virtual double getOutput();
  
    virtual void setActive(bool active = true);

  protected:
    bool mActive = true;
};

}

#endif
