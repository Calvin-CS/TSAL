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
void Synth::noteOn(double note, double velocity) {
  mNote = note;
  mOscillator.setActive();
  mEnvelope.start();
  setVelocity(velocity); 
  mOscillator.setNote(note);
}

void Synth::play(double note, Util::TimeScale scale, unsigned multiplier) {
  noteOn(note);
  Util::thread_sleep(multiplier, scale);
}

void Synth::play(double note, Sequencer::NoteScale scale, unsigned multiplier) {
  noteOn(note);
  Sequencer& seq = getMixer()->getSequencer();
  seq.waitForTick(seq.getTick() + seq.getTicksInNote(scale) * multiplier);
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
