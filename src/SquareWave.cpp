#include "SquareWave.h"

double SquareWave::getWaveformSample(double phase) const {
  return phase < M_PI ? 1 : -1;
}
