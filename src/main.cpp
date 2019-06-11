#include "Oscillator.h"
#include "Chord.h"
#include "Mixer.h"
#include "MidiNotes.h"
#include "Compressor.h"
#include "Channel.h"
#include "MidiFile.h"
#include <iostream>
#include <memory>

#include <omp.h>
#include <chrono>
#include <thread>

using namespace tsal;
using namespace smf;
using namespace std;

void thread_sleep(unsigned milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}


unsigned problemSize = 500;
unsigned numThreads = 2;

int main() {  
  Mixer mixer;
  vector<Oscillator> osc(numThreads);
  for (unsigned i = 0; i < osc.size(); i++) {
    osc[i].setGain(0.2);
    mixer.add(&osc[i]);
  }
    
  MidiFile midifile;
  midifile.read("/home/mark/Downloads/test.mid");
  midifile.joinTracks();

  omp_set_num_threads(numThreads);

  int eventStamps[] = {0, 191, midifile[0].size() - 1};
  double secondsPerTick = ((double) midifile.getFileDurationInSeconds()) / midifile.getFileDurationInTicks();
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    MidiEvent* me;
    for (int event = eventStamps[id]; event < eventStamps[id+1]; event++) {
      me = &midifile[0][event];   
      me->isNoteOn() ? osc[id].start() : osc[id].stop();
      if (me->isNote()) {
        osc[id].setNote(me->getKeyNumber());
        osc[id].setGain(0.5 * (((double) me->getVelocity())/127.0));
      }
      
      thread_sleep((midifile[0][event + 1].tick - me->tick) * secondsPerTick * 1000);
    }
  }
  
  return 0;
}
