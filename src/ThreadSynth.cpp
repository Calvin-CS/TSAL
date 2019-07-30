#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

ThreadSynth::ThreadSynth(Mixer* mixer) : Synth(mixer) {
};

void ThreadSynth::play(double note, Timing::TimeScale scale, unsigned duration) {
  Synth::play(note);
  Util::thread_sleep(duration, scale);
}

void ThreadSynth::play(double note, Timing::NoteScale scale, unsigned duration) {
  Synth::play(note);
  lock(scale, duration);
}

void ThreadSynth::notify() {
  mCondition.notify_one();
}

void ThreadSynth::lock(Timing::NoteScale scale, unsigned duration) {
  Sequencer& seq = mMixer->getSequencer();
  std::unique_lock<std::mutex> lk(mMutex);
  seq.schedule(std::bind(&ThreadSynth::notify, this), scale, duration);
  mCondition.wait(lk);
}


void ThreadSynth::stop(Timing::TimeScale scale, unsigned duration) {
  Synth::stop();
  Util::thread_sleep(duration, scale);
}

void ThreadSynth::stop(Timing::NoteScale scale, unsigned duration) {
  Synth::stop();
  lock(scale, duration);
}


}
