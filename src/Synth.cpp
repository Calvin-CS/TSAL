#include "Synth.hpp"

namespace tsal {

double Synth::getOutput() {
  return mOscillator.getOutput() * mEnvelope.getOutput() * mAmp * (mVelocity / 127.0);
}
  
/**
 * @brief Start playing a note
 * 
 * @param note 
 * @param velocity 
 */
void Synth::noteOn(unsigned note, double velocity) {
  mNote = note;
  mEnvelope.start();
  setVelocity(velocity); 
  mOscillator.setNote(note);
}

/**
 * @brief Stop playing a note. However, this synth is monophonic so the note is irrelavant
 * 
 * @param note 
 */
void Synth::noteOff(unsigned note) {
  mEnvelope.stop();
}

unsigned Synth::getNote() const {
  return mNote;
}

void Synth::setVelocity(double velocity) {
  mVelocity = checkParameterRange("Synth: Velocity", velocity, mVelocityRange);
}

ParameterRange<double> Synth::mVelocityRange = std::make_pair(0.0, 127.0);
}
