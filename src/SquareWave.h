#include "Waveform.h"

#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

namespace tsal {

class SquareWave : public Waveform {
  public:
    double getWaveformSample(double phase) const override {
      return phase < M_PI ? 1 : -1;
    };
};

}
#endif
