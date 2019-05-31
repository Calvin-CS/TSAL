#include "Chord.h"

namespace tsal {

Chord::Chord(unsigned numOscillators, unsigned problemSize, unsigned startNote, unsigned endNote) {
  mProblemSize = problemSize;
  unsigned octave = 0;
  const unsigned sizeOfChord = sizeof(mNoteDeltas)/sizeof(mNoteDeltas[0]);

  for (unsigned i = 0; i < numOscillators; i++) {
    // Calculate the the transposing from the current octave
    unsigned noteOctave = octave * 12;
    
    // Create the OscillatorNode
    OscillatorNode* osc = new OscillatorNode();
    // Set the notes based on our chord, and move up an octave if we run out of chord
    osc->setNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);
    osc->setGain(0.4);

    // Calculate target pitch
    double pitchChange = 
      OscillatorNode::getFrequencyFromNote(endNote + noteOctave + mNoteDeltas[i % sizeOfChord])
        - OscillatorNode::getFrequencyFromNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);


    addNode(osc);
    mOscillatorNodes.push_back(osc);
    mTotalPitchChanges.push_back(pitchChange);

    // Move up an octave for next chord if necessary
    if (i == sizeOfChord - 1) {
      octave += 1;
    }
  }
}

Chord::~Chord() {
  // Clean up the dynamically allocated nodes
  for (unsigned i = 0; i < mOscillatorNodes.size(); i++) {
    // Remove them from the node list
    removeNode(mOscillatorNodes[i]);
    // free the memory
    delete mOscillatorNodes[i];
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
  mOscillatorNodes[id]->start();
  std::cout << "Starting osc: " << id << " at frequency: " 
    << mOscillatorNodes[id]->getFrequency() << std::endl;
}

void Chord::stop(unsigned id) {
  mOscillatorNodes[id]->stop();
  std::cout << "Stopping osc: " << id << " at frequency: " 
    << mOscillatorNodes[id]->getFrequency() << std::endl;
}

void Chord::step(unsigned id) {
  OscillatorNode* osc = mOscillatorNodes[id];

  // Calculate the increment amount
  double inc = 1.0/((double) mProblemSize) * mOscillatorNodes.size();
  // Update the oscillator
  osc->setFrequency(osc->getFrequency() + inc * mTotalPitchChanges[id]);
}

}
