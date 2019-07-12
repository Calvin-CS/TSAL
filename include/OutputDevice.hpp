#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include "Util.hpp"
#include <iostream>

namespace tsal {

// Foward declaration of the Mixer
class Mixer;

/** @class OutputDevice
 * @brief Base class for a device that produces audio output
 * 
 */
class OutputDevice {
  public:
    OutputDevice(){};
    OutputDevice(Mixer* mixer) { mMixer = mixer; };
    virtual ~OutputDevice() {};

    virtual double getOutput();
  
    virtual void setActive(bool active = true);
    void setGain(double gain);
    void setVolume(double volume);
    virtual void setMixer(Mixer *mixer) { mMixer = mixer; };

    double getGain() const;
    double getVolume() const;
    bool isActive() const;

  protected:
    bool mActive = true;
    double mAmp = 1.0;
    Mixer* mMixer = nullptr;
    
    static ParameterRange<double> mGainRange;
    static ParameterRange<double> mVolumeRange;
  private:
    friend class OutputDevice;
};

}

#endif
