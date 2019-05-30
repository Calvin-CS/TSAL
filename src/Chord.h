#include "OscillatorNode.h"
#include "AudioNode.h"
#include <vector>

#ifndef CHORD_H
#define CHORD_H

/** @class Chord
 * @brief An audiolization class that changes pitch 
 * 
 * Chord is an audiolization that starts from one pitch and transitions to another over
 * a period of work or time using the step method in a multithreaded environement
 */
class Chord {
  public:
    /**
     * @brief Construct a new Chord object
     * 
     * @param node a node to append to
     * @param size the number of threads that will be running the chord
     * @param startNote the starting note for the chord
     * @param endNote the target note for the chord pitch change
     */
    Chord(AudioNode* node, unsigned size, unsigned startNote, unsigned endNote);

    ~Chord();

    /**
     * @brief start all the oscillators
     */
    void start();

    /**
     * @brief stop all the oscillators
     */
    void stop();

    /**
     * @brief start a oscillator
     * 
     * @param id the id of the thread and correlating oscillator
     */
    void start(unsigned id);

    /**
     * @brief stop a oscillator
     * 
     * @param id the id of the thread and correlating oscillator
     */
    void stop(unsigned id);

    /**
     * @brief changes the pitch of the oscillator towards the target note
     * 
     * For each bit of work done, the pitch of the oscillator will slowly
     * move towards the target note until it finishes it work. If done correctly
     * the oscillator should be at the target pitch once the work is finished
     * 
     * @param id the id of the thread and correlationg oscillator
     * @param inc the fraction of work or time
     */
    void step(unsigned id, double inc);

  private: 
    std::vector<OscillatorNode*> mOscillatorNodes;
    std::vector<double> mPitchChanges;
    
    unsigned mNoteDeltas[3] = {0, 4, 7};
    unsigned mStartNote;
    unsigned mEndNote;
};

#endif
