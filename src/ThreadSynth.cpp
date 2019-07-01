#include "ThreadSynth.hpp"
#include "MidiSequencer.hpp"

namespace tsal {

void ThreadSynth::noteOn(unsigned note, unsigned tick) {
  waitForEvent(tick);
  Synth::noteOn(note);
}

void ThreadSynth::noteOff(unsigned note, unsigned tick) {
  waitForEvent(tick);
  Synth::noteOff(note);
}

void ThreadSynth::waitForEvent(unsigned tick) {
  std::unique_lock<std::mutex> lk(mSequencer->mutex);
  mSequencer->cond.wait(lk, [this, tick]{return mSequencer->getTick() >= tick;}); 
}

}
