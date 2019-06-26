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
  /*
  oscillator.setMode(tsal::Oscillator::SINE);
  oscillator.setGain(0.1);

  mixer.add(oscillator);
  mixer.add(delay);

  thread_sleep(500);

  oscillator.setActive(false);

  thread_sleep(2000);

  mixer.remove(delay);
  
  oscillator.setActive();
  thread_sleep(1000);
  oscillator.setActive(false);
  */ 
  const unsigned numThreads = 1;
  const unsigned work = 10000; 
  tsal::ProgressOctave progress(tsal::D4, work, numThreads);
  mixer.add(progress);
  omp_set_num_threads(numThreads);
  #pragma omp parallel for
  for (unsigned i = 0; i < work; i++) {
    progress.update(omp_get_thread_num());
    thread_sleep(5);
  }
  
  return 0;
}
