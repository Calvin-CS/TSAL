#include "Filter.hpp"

namespace tsal {

double Filter::process(double input) {
  const double cutoffLow = mMode == LOWPASS ? 0 : mCutoffLow;
  const double cutoffHigh = mMode == HIGHPASS ? 0 : mCutoffHigh;
  const double fbLow = mResonanceLow + mResonanceLow/(1 - cutoffLow);
  const double fbHigh = mResonanceHigh + mResonanceHigh/(1 - cutoffHigh);
  m1 = m1 + cutoffLow*(input - m1 + fbLow*(m1 - m2)) + mPentium4;
  m2 = m2 + cutoffLow*(m1 - m2);
  m3 = m3 + cutoffHigh*(m2 - m3 + fbHigh*(m3 - m4)) + mPentium4;
  m4 = m4 + cutoffHigh*(m3 - m4);
  return m2 - m4;
}

void Filter::setCutoff(double cutoff) {
  // mCutoffLow = mCutoffHigh = Util::checkParameterRangeHiddenCeiling(
}

double Filter::mPentium4 = 1.0e-24;
double Filter::CutoffRangeMax = 0.99999;
Util::ParameterRange<double> Filter::mCutoffRange = std::make_pair(0.0, 1.0);
Util::ParameterRange<double> Filter::mResonanceRange = std::make_pair(0.0, 1.0);
}
