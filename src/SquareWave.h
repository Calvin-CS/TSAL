#include "Waveform.h"

#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

class SquareWave : public Waveform {
  public:
    double getWaveformSample(double phase) const;
};

#endif
