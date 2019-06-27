#include "tsal.hpp"
#include <omp.h>

#include <chrono>
#include <thread>
void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
  tsal::Mixer mixer;
  tsal::Oscillator oscillator;
  tsal::Delay delay;
  oscillator.setMode(tsal::Oscillator::SINE);
  oscillator.setGain(-20);

  mixer.add(oscillator);
  mixer.add(delay);

  thread_sleep(500);

  oscillator.setActive(false);

  thread_sleep(2000);

  mixer.remove(delay);
  
  oscillator.setActive();
  thread_sleep(1000);
  oscillator.setActive(false);
  thread_sleep(10000);
  return 0;
}
