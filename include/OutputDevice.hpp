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
    virtual void setMixer(Mixer *mixer) { mMixer = mixer; };

    void setGain(double gain);
    void setVolume(double volume);

    double getGain() const;
    double getVolume() const;
    bool isActive() const;

  protected:
    Mixer* mMixer = nullptr;
    unsigned getSampleRate() const;
    bool mActive = true;
    double mAmp = 1.0;
    
    static Util::ParameterRange<double> mGainRange;
    static Util::ParameterRange<double> mVolumeRange;
};

}

#endif
