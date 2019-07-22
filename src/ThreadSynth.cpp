#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

/**
 * @brief Start playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOn(double note, double velocity, unsigned tick) {
  if (mMixer == nullptr)
    return;
  mMixer->getSequencer().waitForTick(tick);
  Synth::noteOn(note, velocity);
}

/**
 * @brief Stop playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOff(double note, unsigned tick) {
  if (mMixer == nullptr)
    return;
  mMixer->getSequencer().waitForTick(tick);
  //Synth::noteOff(note);
}

}
