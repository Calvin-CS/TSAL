#include "Chord.h"

Chord::Chord(unsigned size, unsigned startNote, unsigned endNote) {
  for (unsigned i = 0; i < size; i++) {
    Oscillator* osc = new Oscillator();
    osc->setNote(startNote += mNoteDeltas[i]);
    osc->setGain(0.4);
    mOscillators.push_back(osc);
  }
}

Chord::~Chord() {
  for(unsigned i = 0; i < mOscillators.size(); i++) {
    delete mOscillators[i];
  }
}

void Chord::start(unsigned id) {
  mOscillators[id]->start();
  std::cout << "Starting osc: " << id << " at frequency: " 
    << mOscillators[id]->getFrequency() << std::endl;
}

void Chord::stop(unsigned id) {
  mOscillators[id]->stop();
}
