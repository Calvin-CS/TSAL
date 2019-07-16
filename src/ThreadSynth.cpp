#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

/**
 * @brief Start playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOn(unsigned note, double velocity, unsigned tick) {
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
void ThreadSynth::noteOff(unsigned note, unsigned tick) {
  if (mMixer == nullptr)
    return;
  mMixer->getSequencer().waitForTick(tick);
  Synth::noteOff(note);
}

}
