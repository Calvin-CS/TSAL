#define _USE_MATH_DEFINES
#include <math.h>

#ifndef WAVEFORM_H
#define WAVEFORM_H

class Waveform {
  public:
    virtual double getWaveformSample(double phase) { return 0; };
};

#endif
