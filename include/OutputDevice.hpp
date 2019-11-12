#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include "Util.hpp"
#include "AudioBuffer.hpp"
#include <iostream>
#include <vector>

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
    virtual double getOutput() { return 0.0; };
    virtual void getOutput(AudioBuffer<float> &buffer) { return; };
    /**
     * @brief Get the output for the device
     * 
     * @return double 
     */
    virtual void setActive(bool active = true);
    virtual void setMixer(Mixer* mixer) { mMixer = mixer; };

    void setPanning(double panning);
    void setGain(double gain);
    void setVolume(double volume);

    double getLeftPanning() const;
    double getRightPanning() const;
    double getGain() const;
    double getVolume() const;
    bool isActive() const;

  protected:
    Mixer* mMixer = nullptr;
    bool mActive = true;
    double mAmp = 1.0;
    double mPanning = 0.0;
    
    static Util::ParameterRange<double> mGainRange;
    static Util::ParameterRange<double> mVolumeRange;
    static Util::ParameterRange<double> mPanningRange;    
};

}

#endif
