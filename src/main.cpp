#include "OscillatorNode.h"
#include "Chord.h"
#include "TSAudio.h"
#include "CompressorNode.h"
#include <iostream>
#include <memory>

#include <omp.h>
#include <chrono>
#include <thread>

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

const unsigned problemSize = 300;
const unsigned threads = 1;

int main() {  
  omp_set_num_threads(threads);
  
  TSAudio audio;
  CompressorNode* compressor = new CompressorNode();
  audio.addNode(compressor);

  Chord chord(*compressor, threads, 60, 70);
  //thread_sleep(1000);
  
  #pragma omp parallel
  {
    unsigned id = omp_get_thread_num();

    chord.start(id);
    thread_sleep(1000);
    
    #pragma omp for
    for(unsigned i = 1; i <= problemSize; i++) {

      thread_sleep(10);
      chord.step(id, 1.0/((double) problemSize) * omp_get_num_threads() );
    }
    thread_sleep(1000);
  }

  chord.stop();

/*
  std::cout << "\n Press <enter> to stop\n" << std::endl;
  char input;
  std::cin.get(input);
*/
  return 0;
}
