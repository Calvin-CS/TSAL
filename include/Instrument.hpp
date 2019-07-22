#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "OutputDevice.hpp"
#include "Sequencer.hpp"

namespace tsal {

/** @class Instrument
 * @brief An abstract class to provide expected behaviors of instruments
 * 
 */
class Instrument : public OutputDevice {
  public:
    virtual ~Instrument();
    virtual void noteOn(double note, double velocity) {};
    virtual void noteOff(double note) {};
};

}

#endif
