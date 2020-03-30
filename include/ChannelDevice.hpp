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
    ChannelDevice(Mixer* mixer) : OutputDevice(mixer){};
  protected:
    virtual void setParentChannel(Channel* channel) = 0;
    Channel* mParentChannel = nullptr;
};

}

#endif
