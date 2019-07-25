#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

ThreadSynth::ThreadSynth(Mixer* mixer) : Synth(mixer) {
};

/**
 * @brief Start playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOnTest(double note, double velocity, unsigned tick) {
  mMixer->getSequencer().waitForTick(tick);
  Synth::noteOn(note, velocity);
}

/**
 * @brief Stop playing a note after blocking the thread till tick time
 * 
 * @param note 
 * @param tick 
 */
void ThreadSynth::noteOffTest(double note, unsigned tick) {
  mMixer->getSequencer().waitForTick(tick);
  Synth::noteOff();
}

}
