#include "ThreadSynth.hpp"
#include "MidiSequencer.hpp"

namespace tsal {

void ThreadSynth::noteOn(unsigned note, unsigned tick) {
  mSequencer->waitForTick(tick);
  Synth::noteOn(note);
}

void ThreadSynth::noteOff(unsigned note, unsigned tick) {
  mSequencer->waitForTick(tick);
  Synth::noteOff(note);
}

}
