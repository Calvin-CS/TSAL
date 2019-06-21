#include "tsal.hpp"
#include <pthread.h>
#include <vector>

// Temporary fix
#include <chrono>
#include <thread>
#define NUM_THREADS 2

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
// Temporary fix


struct ThreadData {
  tsal::MidiParser* midiParser;
  std::vector<tsal::Oscillator>* voices;
  unsigned tid;
  unsigned start;
  unsigned end;
};

void* ThreadFunction(void* ptr) {
  ThreadData data = *((ThreadData*) ptr);
  auto& voices = *data.voices;
  auto& midiParser = *data.midiParser;

  voices[data.tid].setActive();
  
  for (unsigned i = data.start; i < data.end; i++) {
    auto& me = midiParser[i];  
    if (me.isNote())
      voices[data.tid].playNote(me.getKeyNumber(), me.getVelocity());
    
    thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
  }
  pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Invalid arguments\n\n"
              << "rain <midifile> <tracks>\n" 
              << "\tmidifile = a path to a midifile\n" 
              << "\ttracks = the number of tracks in the midifile\n"
              << std::endl;
    return 0;
  }
  const unsigned numTracks = atoi(argv[2]);
  tsal::MidiParser midiParser(numTracks, argv[1]);

  pthread_t threads[NUM_THREADS];
  ThreadData* threadData[NUM_THREADS];
  tsal::Mixer mixer;
  std::vector<tsal::Oscillator> voices(NUM_THREADS);  

  for (unsigned i = 0; i < voices.size(); i++) {
    voices[i].setGain(0.1);
    voices[i].setActive(false);
    mixer.add(voices[i]);
  }

  unsigned blockSize = midiParser.size() / numTracks;
  for(unsigned i = 0; i < NUM_THREADS; i++ ) {
    unsigned start = i * blockSize;
    unsigned end = start + blockSize;
    threadData[i] = new ThreadData { &midiParser, &voices, i, start, end };  
    pthread_create(&threads[i], NULL, ThreadFunction, (void *) threadData[i]);
  }

  for (unsigned i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    delete threadData[i];
  }

  return 0;
}
