#include "SquareWave.h"

double SquareWave::getWaveformSample(double phase) {
  return phase < M_PI ? 1 : -1;
}
