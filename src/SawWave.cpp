#include "SawWave.h"

double SawWave::getWaveformSample(double phase) const {
  return (2.0 * phase / (2 * M_PI) ) - 1.0;
}
