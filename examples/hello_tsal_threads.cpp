#include "tsal.hpp"
#include <omp.h>

#define NUM_THREADS 4

/** @example hello_tsal_threads.cpp
 *
 * A more complex "Hello World!" example that uses multithreading
 * The main idea is that each synth gets its own thread, and then plays
 * a pitch based on that thread id.
 */
int main() {
  // Create the mixer and array of synths
  tsal::Mixer mixer;
  tsal::Synth synths[NUM_THREADS];

  // Setup omp with a number of threads
  omp_set_num_threads(NUM_THREADS);
  
  // Run the parallel block
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    // Add the synth to the mixer
    mixer.add(synths[id]);
    synths[id].setVolume(0.3);
    
    // Start playing a pitch based on thread number
    synths[id].noteOn(tsal::C4 + 5 * id);
    // Wait for a second
    tsal::thread_sleep(1000);
    // Stop playing 
    synths[id].noteOff();
  }

  return 0;
}
