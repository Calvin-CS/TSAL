#include "ThreadSynth.hpp"
#include "MidiSequencer.hpp"

namespace tsal {

ThreadSynth::ThreadSynth() {
  setActive(false);
}

void ThreadSynth::noteOn(unsigned note, unsigned tick) {
  waitForEvent(tick);
  setNote(note);
  
  setActive();
}

void ThreadSynth::noteOff(unsigned note, unsigned tick) {
  waitForEvent(tick);
  setActive(false);
}

void ThreadSynth::waitForEvent(unsigned tick) {
  std::unique_lock<std::mutex> lk(seq->mutex);
  seq->cond.wait(lk, [tick]{return MidiSequencer::mTick >= tick;}); 
}

}
