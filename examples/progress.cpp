#include "tsal.hpp"
#include <omp.h>
#include <iostream>

/** @example progress.cpp
 * 
 * ProgressOctave is the audio equivalent of a graphical progress bar
 * The progress is conveyed through the ascending pitch. No progress
 * means low pitch, and an almost completed task will be playing at a high
 * pitch. When done in parallel, each thread takes a chunk of the pitch
 * range based on how the omp parallel for pragma divides up the work
 * 
 * Parse the parameters\n
 * Create the mixer and ProgressOctave\n
 * Run parallel block
 * - Update the ProgressOctave
 */
int main(int argc, char* argv[]) {
  const unsigned numThreads = (argc < 2) ? 2 : (unsigned) atoi(argv[1]);
  const unsigned work = (argc < 3) ? 100000000 : (unsigned) atoi(argv[2]);

  tsal::Mixer mixer;
  tsal::ProgressOctave progress(mixer.getContext(), tsal::C4, work, numThreads);

  mixer.add(progress);
  
  omp_set_num_threads(numThreads);
  #pragma omp parallel for
  for (unsigned i = 0; i < work; i++) {
    progress.update(omp_get_thread_num());
  }
  
  return 0;
}
