#ifndef PROGRESSOCTAVE_H
#define PROGRESSOCTAVE_H

#include "Oscillator.hpp"
#include "Instrument.hpp"
#include "RouteDevice.hpp"
#include <vector>

namespace tsal {

/** @class ProgressOctave
 * @brief An instrument that is the equivalent of a progress bar
 *
 * A very basic instrument that when given a starting note, problem size, and number
 * of workers, outputs audio based upon the calculated progress.
 */
class ProgressOctave : public Instrument {
  public:
    ProgressOctave(const Context& context, unsigned startNote, unsigned problemSize, unsigned numWorkers);
    void getOutput(AudioBuffer<float> &buffer) override;
    virtual void setMixer(Mixer* mixer) override;
    void update(unsigned id);
  private:
    unsigned mStartNote;
    unsigned mProblemSize;
    unsigned mNumWorkers;

    std::vector<std::unique_ptr<Oscillator>> mOscillators;
    RouteDevice<Oscillator> mRoutedOscillators;
    double mStepValue;
};
  
}

#endif
