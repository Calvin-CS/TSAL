#include "Synth.hpp"
#include <functional>

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
void Synth::noteOn(double note, double velocity, unsigned duration) {
  mNote = note;
  mOscillator.setActive();
  mEnvelope.start();
  setVelocity(velocity); 
  mOscillator.setNote(note);
  if (duration > 0) {
    std::function< void() > callback = std::bind(&Synth::noteOff, this);
    getMixer()->getSequencer().schedule(duration, callback);
  } 
}

/**
 * @brief Stop playing a note. However, this synth is monophonic so the note is irrelavant
 * 
 * @param note 
 */
void Synth::noteOff() {
  if (mEnvelope.isActive()) {
    mEnvelope.stop();
  } else {
    mOscillator.setActive(false);
  }
}

double Synth::getNote() const {
  return mNote;
}

void Synth::setVelocity(double velocity) {
  mVelocity = Util::checkParameterRange("Synth: Velocity", velocity, mVelocityRange);
}

Util::ParameterRange<double> Synth::mVelocityRange = std::make_pair(0.0, 127.0);

}
