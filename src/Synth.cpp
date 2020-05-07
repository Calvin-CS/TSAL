#include "Synth.hpp"
#include <functional>

namespace tsal {


Synth::Synth() {
  mEnvelope.setActive(false);
  mFilter.setMode(Filter::HIGHPASS);
  mLFO.setMode(Oscillator::SINE);
  mLFO.setFrequency(2);
  mLFO.setActive();
}

void Synth::getOutput(AudioBuffer<float> &buffer) {
  if (!mActive) {
    return;
  }
  const auto channels = buffer.getChannelCount();
  const auto frames = buffer.getFrameCount();

  // setChannelPanning(channels);

  for (unsigned long i = 0; i < frames; i++) {
    const auto envelope = mEnvelope.getSample();
    const auto output = mOscillator.getSample();
    
    const auto lfoFilterMod = (mLFO.getSample() + 1) / 2;
    mFilter.setCutoff(lfoFilterMod);

    for (unsigned j = 0; j < channels; j++) {
      buffer[i * channels + j] = mFilter.process(output * envelope * (mVelocity / 127.0)); 
    }
  }
}
  
/**
 * @brief Start playing a note
 * 
 * @param note 
 * @param velocity 
 */
void Synth::play(double note, double velocity) {
  mNote = note;
  mOscillator.setActive();
  mEnvelope.start();
  setVelocity(velocity); 
  mOscillator.setNote(note);
}


/**
 * @brief Stop playing a note. However, this synth is monophonic so the note is irrelavant
 * 
 * @param note 
 */
void Synth::stop(double note) {
  (void)note;
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
