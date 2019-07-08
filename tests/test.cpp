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
  tsal::Synth synth2;
  tsal::Delay delay;
  tsal::Channel channel;

  mixer.add(channel);
  channel.add(synth);
  channel.add(synth2);
  mixer.add(delay);

  synth2.noteOn(tsal::E4);
  synth.noteOn(tsal::C4);

  thread_sleep(500);

  synth2.noteOff();
  synth.noteOff(tsal::C4);

  thread_sleep(2000);

  mixer.remove(delay);
  synth.noteOn(tsal::C4);
  
  std::cout << -1 % 5 << " " << ((-1 % 5) + 5) % 5 << std::endl;
  thread_sleep(1000);
  synth.noteOff(tsal::C4);
  thread_sleep(1000);

  for (double i = 0.0; i < 2.0; i += 0.1) {
    channel.setVolume(i);
    synth.noteOn(tsal::C4);
    thread_sleep(1000);
    synth.noteOff(tsal::C4);
    thread_sleep(1000);
  }
  
  return 0;
}
