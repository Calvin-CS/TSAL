#include "Chord.h"

Chord::Chord(unsigned size, unsigned startNote, unsigned endNote) {
  mStartNote = startNote;
  mEndNote = endNote;

  unsigned octave = 0;
  const unsigned sizeOfChord = sizeof(mNoteDeltas)/sizeof(mNoteDeltas[0]);

  for (unsigned i = 0; i < size; i++) {
    unsigned noteOctave = octave * 12;
    // Create the oscillator
    Oscillator* osc = new Oscillator();
    osc->setNote(startNote + noteOctave + mNoteDeltas[i % sizeOfChord]);
    osc->setGain(0.4);

    // Calculate target pitch
    double pitchChange = 
      Oscillator::getFrequencyFromNote(mEndNote + noteOctave + mNoteDeltas[i % sizeOfChord])
        - Oscillator::getFrequencyFromNote(mStartNote + noteOctave + mNoteDeltas[i % sizeOfChord]);


    mOscillators.push_back(osc);
    mPitchChanges.push_back(pitchChange);

    // Move up an octave to the next chord
    if (i == sizeOfChord - 1) {
      octave += 1;
    }
  }
}

Chord::~Chord() {
  for(unsigned i = 0; i < mOscillators.size(); i++) {
    delete mOscillators[i];
  }
}

void Chord::start() {
  for(unsigned i = 0; i < mOscillators.size(); i++) {
    start(i);
  }
}

void Chord::stop() {
  for(unsigned i = 0; i < mOscillators.size(); i++) {
    stop(i);
  }
}

void Chord::start(unsigned id) {
  mOscillators[id]->start();
  std::cout << "Starting osc: " << id << " at frequency: " 
    << mOscillators[id]->getFrequency() << std::endl;
}

void Chord::stop(unsigned id) {
  mOscillators[id]->stop();
  std::cout << "Stopping osc: " << id << " at frequency: " 
    << mOscillators[id]->getFrequency() << std::endl;
}

void Chord::step(unsigned id, double inc) {
  Oscillator* osc = mOscillators[id];
  osc->setFrequency(osc->getFrequency() + inc * mPitchChanges[id]);
}
