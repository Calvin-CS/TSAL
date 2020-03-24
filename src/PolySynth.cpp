#include "PolySynth.hpp"

namespace tsal {

PolySynth::PolySynth(Mixer* mixer) : Instrument(mixer), mVoices(NUM_VOICES, Synth(mixer)), mRoutedSynths(mixer) {
  for (unsigned i = 0; i < mVoices.size(); i++) {
    mVoices[i].setActive(false);
    mVoices[i].setVolume(0.3);
    mRoutedSynths.add(mVoices[i]);
  }
}

void PolySynth::getOutput(AudioBuffer<float> &buffer) {
  mRoutedSynths.getOutput(buffer);
}

/* @brief Play a note with velocity
 *
 * @param note
 * @param velocity
 */
void PolySynth::play(double note, double velocity) {
  Synth* voice = getInactiveVoice();
  if (voice == nullptr) {
    // Maybe change the behavior to grab the nearest note 
    return;
  }
  voice->play(note, velocity);
}

/* @brief Stop playing a note
 *
 * @param note
 */
void PolySynth::stop(double note) {
  for (unsigned i = 0; i < mVoices.size(); i++) {
    if (mVoices[i].getNote() == note) {
      mVoices[i].stop();
      mVoices[i].setActive(false);
    }
  }
}

/* @brief Set the mode of the underlying synths
 *
 * @param mode
 */
void PolySynth::setMode(Oscillator::OscillatorMode mode) {
  for (unsigned i = 0; i < mVoices.size(); i++) {
    mVoices[i].setMode(mode);
  }
}

Synth* PolySynth::getInactiveVoice() {
  // Whenever a note is pressed, an inactive voice needs to be found an played
  // If all the voices are active, a nullptr is returned
  Synth* voice = nullptr;
  for (unsigned i = 0; i < mVoices.size(); i++) {
    if (!mVoices[i].isActive()) {
      voice = &mVoices[i];
      voice->setActive();
      break;
    }
  }
  return voice;
}

PolySynth& PolySynth::operator=(const PolySynth& synth) {
  if (&synth != this) {
    mMode = synth.mMode;
    mVoices = std::vector<Synth>();

    for (Synth s : mVoices) {
      mRoutedSynths.remove(s);
    }

    for (Synth s : synth.mVoices) {
      Synth copy = Synth(s);
      mVoices.push_back(std::move(copy));
      mRoutedSynths.add(s);
    }
  }

  return *this;
}

}
