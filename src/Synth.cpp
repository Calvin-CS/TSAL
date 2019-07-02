#include "Synth.hpp"

namespace tsal {

double Synth::getOutput() {
  return mOscillator.getOutput() * mEnvelope.getEnvelope() * mAmp;
}
  
/**
 * @brief Start playing a note
 * 
 * @param note 
 * @param velocity 
 */
void Synth::noteOn(unsigned note, double velocity) {
  mEnvelope.start();
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

}
