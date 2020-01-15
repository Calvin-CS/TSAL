#include "tsal.hpp"
#include <omp.h>

/** @example hello_tsal_threads.cpp
 *
 * A more complex "Hello World!" example that uses multithreading
 * The main idea is that each synth gets its own thread, and then plays
 * a pitch based on that thread id.
 */
int main(int argc, char* argv[]) {
  int numThreads = (argc == 2) ? atoi(argv[1]) : 2;
  if (numThreads == 0) {
    std::cout << "\nhello_tsal_threads <num_threads>\n"
              << "\tnum_threads = the number of threads\n"
              << std::endl;
    return 0;
  }
      
  // Create the mixer and array of synths
  tsal::Mixer mixer;

  // Setup omp with a number of threads
  omp_set_num_threads(numThreads);
  
  // Run the parallel block
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    tsal::Synth synth;
    // Add the synth to the mixer
    std::cout << "adding synth" << std::endl;
    mixer.add(synth);
    synth.setMode(tsal::Oscillator::SAW);
    // Start playing a pitch based on thread number
    synth.play(tsal::C4 + 5 * id);
    // Wait for a second
    tsal::Util::thread_sleep(5000);
    // Stop playing 
    synth.stop();
  }

  return 0;
}
