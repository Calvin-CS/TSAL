#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include "Util.hpp"
#include "AudioBuffer.hpp"
#include "Context.hpp"
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
    OutputDevice(const Context& context);
    virtual ~OutputDevice() {};
    /**
     * @brief Get the output for the device
     * 
     * @return double 
     */
    virtual void getOutput(AudioBuffer<float> &buffer) { return; };
    virtual void setActive(bool active = true);
    virtual void updateContext(const Context& context) { mContext.update(context); };

    void setPanning(double panning);
    void setGain(double gain);
    void setVolume(double volume);

    double getGain() const;
    double getVolume() const;
    bool isActive() const;

  protected:
    virtual void setChannelPanning(unsigned channelCount);
    bool mActive = true;
    Context mContext;
    double mAmp = 1.0;
    double mPanning = 0.0;
    std::vector<double> mChannelPanning;
    
    static Util::ParameterRange<double> mGainRange;
    static Util::ParameterRange<double> mVolumeRange;
    static Util::ParameterRange<double> mPanningRange;    
};

}

#endif
