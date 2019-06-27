#include "Synth.hpp"

namespace tsal {

double Synth::getOutput() {
  return mOscillator.getOutput() * mEnvelope.getEnvelope();
}
  
void Synth::noteOn(unsigned note, double velocity) {
  mEnvelope.start();
  mOscillator.setNote(note);
}

void Synth::noteOff(unsigned note) {
  mEnvelope.stop();
}

}
