#ifndef FILTER_H
#define FILTER_H

#include "Util.hpp"
#include "ParameterManager.hpp"

namespace tsal {

/** @class Filter 
 * @brief Applies a filter (low, high, band) to given audio sample 
 */
class Filter : public ParameterManager {
  public:
    Filter() :
      ParameterManager({
                        { .name="Filter Mode", .min=0.0, .max=2.0, .defaultValue=LOWPASS },
                        { .name="Cutoff", .min=0.0, .max=1.0, .defaultValue=0.0, .exclusiveMax=true },
                        { .name="Resonance", .min=0.0, .max=1.0, .defaultValue=0.0 },
        }) {};

    enum Parameters {
                     FILTER_MODE=0,
                     CUTOFF,
                     RESONANCE,
    };
    enum FilterMode {
      LOWPASS=0,
      HIGHPASS,
      BANDPASS
    };

    double process(double input);

    void setMode(FilterMode mode) { mMode = mode; };
    void setCutoff(double cutoff);
    void setResonance(double resonance);
    
  private:
    FilterMode mMode = LOWPASS;

    double m1, m2, m3, m4 = 0.0;
    static double mPentium4;

};

}
#endif
