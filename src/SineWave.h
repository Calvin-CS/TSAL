#include "Waveform.h"

#ifndef SINEWAVE_H
#define SINEWAVE_H

class SineWave : public Waveform {
  public:
    double getWaveformSample(double phase) const override;
};

#endif
