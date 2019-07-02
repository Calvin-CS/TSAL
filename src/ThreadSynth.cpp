#include "ThreadSynth.hpp"
#include "MidiSequencer.hpp"

namespace tsal {

/**
 * @brief Start playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOn(unsigned note, unsigned tick) {
  mSequencer->waitForTick(tick);
  Synth::noteOn(note);
}

/**
 * @brief Stop playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOff(unsigned note, unsigned tick) {
  mSequencer->waitForTick(tick);
  Synth::noteOff(note);
}

}
