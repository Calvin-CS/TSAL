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
    void setGain(double gain);
    void setVolume(double volume);

    double getGain() const;
    double getVolume() const;

  protected:
    bool mActive = true;
    double mAmp = 1.0;
    static ParameterRange<double> mGainRange;
    static ParameterRange<double> mVolumeRange;
};

}

#endif
