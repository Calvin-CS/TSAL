#include "Waveform.h"

#ifndef SAWWAVE_H
#define SAWWAVE_H

namespace tsal {

class SawWave : public Waveform {
  public:
    double getWaveformSample(double phase) const override {
      return (2.0 * phase / (2 * M_PI) ) - 1.0;
    };
};

}
#endif
