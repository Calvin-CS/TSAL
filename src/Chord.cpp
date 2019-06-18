#include "Chord.hpp"

namespace tsal {

/**
  * @brief Construct a new Chord object
  * 
  * @param numThreads correlates to the number of threads that will be running the chord
  * @param problemSize the number of iterations or amount of work to compute
  * @param startNote the starting note for the chord
  * @param endNote the target note for the chord pitch change
  */
Chord::Chord(unsigned numOscillators, unsigned problemSize, unsigned startNote, unsigned endNote) {
  mProblemSize = problemSize;
  unsigned octave = 0;
  const unsigned sizeOfChord = sizeof(mNoteDeltas)/sizeof(mNoteDeltas[0]);

  for (unsigned i = 0; i < numOscillators; i++) {
    // Calculate the the transposing from the current octave
    unsigned noteOctave = octave * 12;
    
    // Create the Oscillator
    Oscillator* osc = new Oscillator();
    // Set the notes based on our chord, and move up an octave if we run out of chord
    osc->setNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);
    osc->setGain(0.2);

    // Calculate target pitch
    double pitchChange = 
      Oscillator::getFrequencyFromNote(endNote + noteOctave + mNoteDeltas[i % sizeOfChord])
        - Oscillator::getFrequencyFromNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);
        
    // Store everything in vectors
    router.add(*osc);
    mTotalPitchChanges.push_back(pitchChange);

    // Move up an octave for next chord if necessary
    if (i == sizeOfChord - 1) {
      octave += 1;
    }
  }
}

Chord::~Chord() {
  const std::vector<Oscillator*> oscillators = router.getInputDevices();
  // Clean up the dynamically allocated nodes
  for (unsigned i = 0; i < oscillators.size(); i++) {
    // Remove them from the node list
    //remove(mOscillators[i]);
    // free the memory
    delete oscillators[i];
  }
}

/**
  * @brief start all the oscillators
  */
void Chord::start() {
  for(unsigned i = 0; i < router.getInputDevices().size(); i++) {
    start(i);
  }
}

/**
  * @brief stop all the oscillators
  */
void Chord::stop() {
  for(unsigned i = 0; i < router.getInputDevices().size(); i++) {
    stop(i);
  }
}

/**
  * @brief start a oscillator
  * 
  * @param id the id of the thread and correlating oscillator
  */
void Chord::start(unsigned id) {
  const std::vector<Oscillator*> oscillators = router.getInputDevices();
  oscillators[id]->setActive(true);
  std::cout << "Starting osc: " << id << " at frequency: " 
    << oscillators[id]->getFrequency() << std::endl;
}

/**
  * @brief stop a oscillator
  * 
  * @param id the id of the thread and correlating oscillator
  */
void Chord::stop(unsigned id) {
  const std::vector<Oscillator*> oscillators = router.getInputDevices();
  oscillators[id]->setActive(false);
  std::cout << "Stopping osc: " << id << " at frequency: " 
    << oscillators[id]->getFrequency() << std::endl;
}

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
void Chord::step(unsigned id) {
  Oscillator* osc = router.getInputDevices()[id];

  // Calculate the increment amount
  double inc = 1.0/((double) mProblemSize) * router.getInputDevices().size();
  // Update the oscillator
  osc->setFrequency(osc->getFrequency() + inc * mTotalPitchChanges[id]);
}

}
