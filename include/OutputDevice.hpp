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
    OutputDevice() = default;
    virtual ~OutputDevice() {};
    /**
     * @brief Get the output for the device
     * 
     * @return double 
     */
    virtual void getOutput(AudioBuffer<float>& buffer) { (void)buffer; return; };
    virtual void setActive(bool active = true);
    virtual void updateContext(const Context& context) { mContext.update(context); };

    bool isActive() const;

  protected:
    bool mActive = true;
    Context mContext;
};

}

#endif
