#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "ChannelDevice.hpp"
#include "Sequencer.hpp"

namespace tsal {

/** @class Instrument
 * @brief An abstract class to provide expected behaviors of instruments
 * 
 */
class Instrument : public ChannelDevice {
  public:
    Instrument() = default;
    virtual void play(double note, double velocity = 100.0) = 0;
    virtual void stop(double note) = 0;
    virtual ~Instrument();
    virtual void setParentChannel(Channel* channel) override;
};

}

#endif
