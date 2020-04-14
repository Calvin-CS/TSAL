#ifndef FILTER_H
#define FILTER_H

#include "Util.hpp"

namespace tsal {

/** @class Filter 
 * @brief Applies a filter (low, high, band) to given audio sample 
 */
class Filter {
  public:
    enum FilterMode {
      LOWPASS,
      HIGHPASS,
      BANDPASS
    };

    double process(double input);

    void setMode(FilterMode mode) { mMode = mode; };
    void setCutoff(double cutoff);
    void setResonance(double resonance);
    
  private:
    FilterMode mMode = LOWPASS;
    double mCutoffLow = 0.5;
    double mCutoffHigh = 0.5;
    double mResonanceLow = 0.5;
    double mResonanceHigh = 0.5;

    double m1, m2, m3, m4 = 0.0;
    static double mPentium4;

    static double CutoffRangeMax;
    static Util::ParameterRange<double> mCutoffRange;
    static Util::ParameterRange<double> mResonanceRange;
};

}
#endif
