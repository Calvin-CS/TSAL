#include "tsal.hpp"
#include <omp.h>

int main(int argc, char* argv[]) {
  const unsigned numThreads = (argc < 2) ? 2 : (unsigned) atoi(argv[1]);
  const unsigned work = (argc < 3) ? 100000000 : (unsigned) atoi(argv[2]);

  tsal::Mixer mixer;
  tsal::ProgressOctave progress(tsal::C4, work, numThreads);

  mixer.add(progress);
  
  omp_set_num_threads(numThreads);
  #pragma omp parallel for
  for (unsigned i = 0; i < work; i++) {
    progress.update(omp_get_thread_num());
  }
  
  return 0;
}
