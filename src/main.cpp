#include "Oscillator.h"
#include "Chord.h"
#include <iostream>
#include <memory>

#include <omp.h>
#include <chrono>
#include <thread>

int main() {
  TSAudio audio;

  const unsigned threads = 5;
  omp_set_num_threads(threads);

  Chord chord(&audio, threads, 48, 60);
  
  #pragma omp parallel
  {
    unsigned id = omp_get_thread_num();

    chord.start(id);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    
    #pragma omp for
    for(int i = 1; i <= 400; i++) {

      std::this_thread::sleep_for(std::chrono::milliseconds(5));
      chord.step(id, 1.0/400.0 * omp_get_num_threads() );
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    
  }
  chord.stop();

/*
  std::cout << "\n Press <enter> to stop\n" << std::endl;
  char input;
  std::cin.get(input);
*/
  return 0;
}
