#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "OutputDevice.hpp"
#include "MidiSequencer.hpp"

namespace tsal {

class Instrument : public OutputDevice {
  public:
    virtual void noteOn(unsigned note, double velocity) {};
    virtual void noteOff(unsigned note) {};
    void setSequencer(MidiSequencer* sequencer) { mSequencer = sequencer; }
  protected:
    MidiSequencer* mSequencer;
};

}

#endif
