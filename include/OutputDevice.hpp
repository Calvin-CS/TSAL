#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include "Util.hpp"
#include <iostream>

namespace tsal {

// Forward declarations
class Mixer;

/** @class OutputDevice
 * @brief Base class for a device that produces audio output
 * 
 */
class OutputDevice {
  public:
    OutputDevice(Mixer* mixer);
    virtual ~OutputDevice() {};
    virtual double getOutput(){ return 0.0; };
    /**
     * @brief Get the output for the device
     * 
     * @return double 
     */
    virtual void setActive(bool active = true);
    virtual void setMixer(Mixer* mixer) { mMixer = mixer; };

    void setGain(double gain);
    void setVolume(double volume);

    double getGain() const;
    double getVolume() const;
    bool isActive() const;

  protected:
    Mixer* mMixer = nullptr;
    bool mActive = true;
    double mAmp = 1.0;
    
    static Util::ParameterRange<double> mGainRange;
    static Util::ParameterRange<double> mVolumeRange;
};

}

#endif
