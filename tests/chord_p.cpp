#include "Mixer.h"
#include "Oscillator.h"
#include "MidiParser.h"
#include "MidiNotes.h"
#include <pthread.h>
#include <vector>

// Temporary fix
#include <chrono>
#include <thread>
#define NUM_THREADS 3

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
// Temporary fix


struct ThreadData {
  std::vector<tsal::Oscillator>* voices;
  unsigned tid;
  unsigned start;
  unsigned end;
};

void* ThreadFunction(void* ptr) {
  ThreadData data = *((ThreadData*) ptr);

  for (unsigned i = data.start; i < data.end; i++) {
    (*data.voices)[data.tid].setFrequency((*data.voices)[data.tid].getFrequency() + 10);
    thread_sleep(100);
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  pthread_t threads[NUM_THREADS];

  tsal::Mixer mixer;
  std::vector<tsal::Oscillator> voices(NUM_THREADS);  

  tsal::MidiNote chord[3] = {tsal::C4, tsal::E4, tsal::G4};
  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(0.1);
    voices[i].setNote(chord[i]);
    mixer.add(voices[i]);
  }

  for(unsigned i = 0; i < NUM_THREADS; i++ ) {
    ThreadData* data = new ThreadData {
      &voices,
      i,
      0,
      100/NUM_THREADS
    };  

    pthread_create(&threads[i], NULL, ThreadFunction, (void *) data);
  }

  for (unsigned i = 0; i < 1; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
