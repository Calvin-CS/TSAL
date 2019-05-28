#include "SineWave.h"

double SineWave::getWaveformSample(double phase) const {
  return sin(phase);
}
