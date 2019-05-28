#include "Waveform.h"

#ifndef SAWWAVE_H
#define SAWWAVE_H

class SawWave : public Waveform {
  public:
    double getWaveformSample(double phase) const;
};

#endif
