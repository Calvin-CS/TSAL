#include "tsal.hpp"
#include <omp.h>

#include <chrono>
#include <thread>
void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
  tsal::Mixer mixer;
  tsal::Synth synth;
  tsal::Delay delay;

  mixer.add(synth);
  mixer.add(delay);

  synth.noteOn(tsal::C4);

  thread_sleep(500);

  synth.noteOff(tsal::C4);

  thread_sleep(2000);

  mixer.remove(delay);
  synth.noteOn(tsal::C4);
  
  thread_sleep(1000);
  synth.noteOff(tsal::C4);
  thread_sleep(10000);
  return 0;
}
