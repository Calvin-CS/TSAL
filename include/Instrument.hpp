#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "OutputDevice.hpp"

namespace tsal {

class Instrument : public OutputDevice {
  public:
    virtual void noteOn(unsigned note, double velocity = 100.0) {};
    virtual void noteOff(unsigned note) {};
};

}

#endif
