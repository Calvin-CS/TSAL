#include "tsal.hpp"
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
  tsal::MidiParser* midiParser;
  std::vector<tsal::Oscillator>* voices;
  unsigned tid;
};

void* ThreadFunction(void* ptr) {
  ThreadData data = *((ThreadData*) ptr);
  auto& voices = *data.voices;
  auto& midiParser = *data.midiParser;

  thread_sleep(data.tid * midiParser.quaterNoteMs(4));
  voices[data.tid].setActive();
  
  for (unsigned i = 0; i < midiParser.size() - 1; i++) {
    auto& me = midiParser[i];
    if (me.isNoteOn())
      voices[data.tid].playNote(me.getKeyNumber(), me.getVelocity());

    thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
    voices[data.tid].stop();
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Invalid arguments\n\n"
              << "jubilate <midifile> <voices>\n" 
              << "\tmidifile = a path to a midifile\n" 
              << "\tvoices = the number of voices (<6)\n"
              << std::endl;
    return 0;
  }
  tsal::MidiParser midiParser(1, argv[1]);
  // const unsigned numVoices = atoi(argv[2]);

  pthread_t threads[NUM_THREADS];
  ThreadData* threadData[NUM_THREADS];
  tsal::Mixer mixer;
  std::vector<tsal::Oscillator> voices(NUM_THREADS);  

  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(0.1);
    voices[i].setActive(false);
    mixer.add(voices[i]);
  }

  for(unsigned i = 0; i < NUM_THREADS; i++ ) {
    threadData[i] = new ThreadData { &midiParser, &voices, i };  
    pthread_create(&threads[i], NULL, ThreadFunction, (void *) threadData[i]);
  }

  for (unsigned i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    delete threadData[i];
  }

  return 0;
}
