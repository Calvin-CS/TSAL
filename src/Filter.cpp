#include "Filter.hpp"

namespace tsal {

double Filter::process(double input) {
  // https://www.musicdsp.org/en/latest/Filters/131-cascaded-resonant-lp-hp-filter.html
  const double cutoff = getParameter(CUTOFF);
  const double resonance = getParameter(RESONANCE);
  const double cutoffLow = getParameter<FilterMode>(FILTER_MODE) == LOWPASS ? getParameterData(CUTOFF).max : cutoff;
  const double cutoffHigh = getParameter<FilterMode>(FILTER_MODE) == HIGHPASS ? getParameterData(CUTOFF).max : cutoff;
  const double fbLow = resonance + resonance/(1 - cutoffLow);
  const double fbHigh = resonance + resonance/(1 - cutoffHigh);
  m1 = m1 + cutoffLow*(input - m1 + fbLow*(m1 - m2)) + mPentium4;
  m2 = m2 + cutoffLow*(m1 - m2);
  m3 = m3 + cutoffHigh*(m2 - m3 + fbHigh*(m3 - m4)) + mPentium4;
  m4 = m4 + cutoffHigh*(m3 - m4);
  return m2 - m4;
}

void Filter::setCutoff(double cutoff) {
  setParameter(CUTOFF, cutoff);
}

void Filter::setResonance(double resonance) {
  setParameter(RESONANCE, resonance);
}

double Filter::mPentium4 = 1.0e-24;
}
