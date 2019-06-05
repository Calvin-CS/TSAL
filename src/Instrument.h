#include "OutputDevice.h"
#include "InputDevice.h"

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

namespace tsal {

class Instrument : public OutputDevice, protected InputDevice {
};

};

#endif
