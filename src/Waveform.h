#define _USE_MATH_DEFINES
#include <cmath>

#ifndef WAVEFORM_H
#define WAVEFORM_H

namespace tsal {

/** @class Waveform
 * @brief Defines a waveform that can be sampled
 * 
 * Waveform generates a waveform sample in the range of 1 to -1 which will
 * be properly scaled by OscillatorNode for audio output
 */
class Waveform {
  public:
    /** @brief Get a sample from the waveform
     * 
     * @param phase the point in the wavefrom to sample
     * 
     * @return double the sample of the waveform with range [-1, 1]
     */
    virtual double getWaveformSample(double phase) const { return 0; };
};

}
#endif
