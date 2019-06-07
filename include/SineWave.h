#include "Waveform.h"

#ifndef SINEWAVE_H
#define SINEWAVE_H

namespace tsal {

class SineWave : public Waveform {
  public:
    double getWaveformSample(double phase) const override {
      return sin(phase);
    };
};

}
#endif
