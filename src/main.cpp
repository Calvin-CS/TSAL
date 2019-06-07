#include "Oscillator.h"
#include "Chord.h"
#include "Mixer.h"
#include "MidiNotes.h"
#include "Compressor.h"
#include "Channel.h"
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

 // mixer.add(&chord);
  Channel chan;
  
  Oscillator osc;
  osc.setGain(1);


  Oscillator osc2;
  osc.setNote(C4);
  
  mixer.add(&chan);
  
  chan.add(&osc);

  thread_sleep(1000);
  osc.setGain(0.2);
  thread_sleep(1000);
  
  chan.remove(&osc);
  
  thread_sleep(1000);
  
  osc.setMode(Oscillator::SAW);

  thread_sleep(1000);
  osc.setActive(false);
  Chord chord(numThreads, problemSize);
  chan.add(&chord);
  
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
  
  return 0;
}
