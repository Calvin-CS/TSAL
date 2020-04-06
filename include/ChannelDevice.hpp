#ifndef CHANNELDEVICE_H
#define CHANNELDEVICE_H

#include "OutputDevice.hpp"

namespace tsal {

//Forward declaration of Channel
class Channel;

/** @class ChannelDevice
 * @brief Base class for a device that can be routed to a channel
 */
class ChannelDevice : public OutputDevice {
  public:
    ChannelDevice() = default;
    void setPanning(double panning);
  protected:
    virtual void setChannelPanning(unsigned channelCount);
    virtual void setParentChannel(Channel* channel) = 0;
    Channel* mParentChannel = nullptr;

    double mPanning = 0.0;
    std::vector<double> mChannelPanning;

    static Util::ParameterRange<double> mPanningRange;    
};

}

#endif
