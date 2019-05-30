#include "Chord.h"


Chord::Chord(TSAudio &audio, unsigned size, unsigned startNote, unsigned endNote) {
  mStartNote = startNote;
  mEndNote = endNote;

  unsigned octave = 0;
  const unsigned sizeOfChord = sizeof(mNoteDeltas)/sizeof(mNoteDeltas[0]);

  for (unsigned i = 0; i < size; i++) {
    unsigned noteOctave = octave * 12;
    
    // Create the OscillatorNode
    OscillatorNode* osc = new OscillatorNode(96000);
    osc->setNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);
    osc->setGain(0.1);
    audio.addNode(osc);

    // Calculate target pitch
    double pitchChange = 
      OscillatorNode::getFrequencyFromNote(mEndNote + noteOctave + mNoteDeltas[i % sizeOfChord])
        - OscillatorNode::getFrequencyFromNote(mStartNote + noteOctave + mNoteDeltas[i % sizeOfChord]);


    mOscillatorNodes.push_back(osc);
    mPitchChanges.push_back(pitchChange);

    // Move up an octave to the next chord
    if (i == sizeOfChord - 1) {
      octave += 1;
    }
  }
}

Chord::~Chord() {
  for(unsigned i = 0; i < mOscillatorNodes.size(); i++) {
    //delete mOscillatorNodes[i];
  }
}

void Chord::start() {
  for(unsigned i = 0; i < mOscillatorNodes.size(); i++) {
    start(i);
  }
}

void Chord::stop() {
  for(unsigned i = 0; i < mOscillatorNodes.size(); i++) {
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

void Chord::step(unsigned id, double inc) {
  OscillatorNode* osc = mOscillatorNodes[id];
  osc->setFrequency(osc->getFrequency() + inc * mPitchChanges[id]);
}
