#include "Oscillator.h"
#include "Chord.h"
#include "TSAudio.h"
#include "MidiNotes.h"
#include "Compressor.h"
#include <iostream>
#include <memory>

#include <omp.h>
#include <chrono>
#include <thread>

using namespace tsal;

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

const unsigned problemSize = 300;
const unsigned numThreads = 4;

int main() {  
  
  omp_set_num_threads(numThreads);
  
  Mixer mixer;

  // Chord chord(numThreads, problemSize, C4, C5);
  // mixer.add(&chord);
  Oscillator osc;
  mixer.add(&osc);
  thread_sleep(1000);
  /*
  #pragma omp parallel
  {
    unsigned id = omp_get_thread_num();

    chord.start(id);
    thread_sleep(1000);
    
    #pragma omp for
    for(unsigned i = 1; i <= problemSize; i++) {
      thread_sleep(10); 
      chord.step(id);
    }
    thread_sleep(1000);
  }
  chord.stop();
  audio.removeNode(&chord);
*/
  return 0;
}
