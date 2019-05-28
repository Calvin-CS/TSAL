#include "Oscillator.h"
#include <vector>

#ifndef CHORD_H
#define CHORD_H

class Chord {
  public:
    Chord(unsigned size, unsigned startNote, unsigned endNote);
    ~Chord();
    void start();
    void stop();
    void start(unsigned id);
    void stop(unsigned id);
    void step(unsigned id, double inc);

  private: 
    std::vector<Oscillator*> mOscillators;
    std::vector<double> mPitchChanges;
    
    unsigned mNoteDeltas[3] = {0, 4, 7};
    unsigned mStartNote;
    unsigned mEndNote;
};

#endif
