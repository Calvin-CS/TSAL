#include "tsal.hpp"
#include <omp.h>
#include <vector>

#define NUM_THREADS 3

int main() {
  tsal::Mixer mixer;
  std::vector<tsal::Oscillator> voices(NUM_THREADS);  

  tsal::MidiNote chord[] = {tsal::C4, tsal::E4, tsal::G4};
  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(-20);
    voices[i].setNote(chord[i]);
    mixer.add(voices[i]);
  }

  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();

    #pragma omp for
    for (unsigned i = 0; i < 100; i++) {
      voices[id].setFrequency(voices[id].getFrequency() + 10);
      tsal::Util::thread_sleep(100);
    }

  }
  return 0;
}
