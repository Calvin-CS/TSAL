#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

ThreadSynth::ThreadSynth(Mixer* mixer) : Synth(mixer) {
};

void ThreadSynth::play(double note, Timing::TimeScale scale, unsigned multiplier) {
  Synth::play(note);
  Util::thread_sleep(multiplier, scale);
}

void ThreadSynth::play(double note, Timing::NoteScale scale, unsigned multiplier) {
  Synth::play(note);
  Sequencer& seq = mMixer->getSequencer();
  seq.waitForTick(seq.getTick() + seq.getTicksInNote(scale) * multiplier);
}


void ThreadSynth::stop(Timing::TimeScale scale, unsigned multiplier) {
  Synth::stop();
  Util::thread_sleep(multiplier, scale);
}

void ThreadSynth::stop(Timing::NoteScale scale, unsigned multiplier) {
  Synth::stop();
  Sequencer& seq = mMixer->getSequencer();
  seq.waitForTick(seq.getTick() + seq.getTicksInNote(scale) * multiplier);
}


}
