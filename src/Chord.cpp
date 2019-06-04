#include "Chord.h"
/*
namespace tsal {

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
    osc->setGain(0.1);

    // Calculate target pitch
    double pitchChange = 
      Oscillator::getFrequencyFromNote(endNote + noteOctave + mNoteDeltas[i % sizeOfChord])
        - Oscillator::getFrequencyFromNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);


    addNode(osc);
    mOscillators.push_back(osc);
    mTotalPitchChanges.push_back(pitchChange);

    // Move up an octave for next chord if necessary
    if (i == sizeOfChord - 1) {
      octave += 1;
    }
  }
}

Chord::~Chord() {
  // Clean up the dynamically allocated nodes
  for (unsigned i = 0; i < mOscillators.size(); i++) {
    // Remove them from the node list
    removeNode(mOscillators[i]);
    // free the memory
    delete mOscillators[i];
  }
}

void Chord::start() {
  for(unsigned i = 0; i < mAudioNodes.size(); i++) {
    start(i);
  }
}

void Chord::stop() {
  for(unsigned i = 0; i < mAudioNodes.size(); i++) {
    stop(i);
  }
}

void Chord::start(unsigned id) {
  mOscillators[id]->setActive(true);
  std::cout << "Starting osc: " << id << " at frequency: " 
    << mOscillators[id]->getFrequency() << std::endl;
}

void Chord::stop(unsigned id) {
  mOscillators[id]->setActive(false);
  std::cout << "Stopping osc: " << id << " at frequency: " 
    << mOscillators[id]->getFrequency() << std::endl;
}

void Chord::step(unsigned id) {
  Oscillator* osc = mOscillators[id];

  // Calculate the increment amount
  double inc = 1.0/((double) mProblemSize) * mOscillators.size();
  // Update the oscillator
  osc->setFrequency(osc->getFrequency() + inc * mTotalPitchChanges[id]);
}

}
*/
