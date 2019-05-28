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
    void incrementNoteFrequency(unsigned id);

  private: 
    std::vector<Oscillator*> mOscillators;
    unsigned mNoteDeltas[3] = {0, 4, 3};
    unsigned mStartNote;
    unsigned mEndNote;
};

#endif
