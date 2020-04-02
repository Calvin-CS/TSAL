#include "ThreadSynth.hpp"
#include "Sequencer.hpp"

namespace tsal {

void ThreadSynth::play(double note, Timing::TimeScale scale, unsigned duration) {
  Synth::play(note);
  Util::thread_sleep(duration, scale);
}

void ThreadSynth::stop(Timing::TimeScale scale, unsigned duration) {
  Synth::stop();
  Util::thread_sleep(duration, scale);
}

}
