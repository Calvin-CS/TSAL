#include "Oscillator.hpp"
#include "Instrument.hpp"
#include "RouteDevice.hpp"
#include "MidiNotes.hpp"
#include <vector>

#ifndef CHORD_H
#define CHORD_H

namespace tsal {
  
/** @class Chord
 * @brief An audiolization class that changes pitch 
 * 
 * Chord is an audiolization that starts from one pitch and transitions to another over
 * a period of work or time using the step method in a multithreaded environement
 */
class Chord : public Instrument {
  public:
    Chord(unsigned numOscillators, unsigned problemSize, unsigned startNote = C4, unsigned endNote = C5);

    ~Chord();

    virtual double getOutput() override {
      return router.getOutput();
    }

    void start();
    void stop();
    void start(unsigned id);
    void stop(unsigned id);
    void step(unsigned id);

  private: 
    RouteDevice<Oscillator> router;
    std::vector<double> mTotalPitchChanges;
    
    unsigned mNoteDeltas[4] = {0, 4, 7, 11};
    unsigned mProblemSize;
};

}
#endif
