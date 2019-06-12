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

  double secondsPerTick = ((double) midifile.getFileDurationInSeconds()) / midifile.getFileDurationInTicks();

  vector<int> regionSize;
  int previousEventIndex = 0;
  for (unsigned i = 0; i < numThreads; i++) {
    int tick = (i+1) * midifile.getFileDurationInTicks()/numThreads;
    for (int j = 0; j < midifile[0].size(); j++) {
      if (midifile[0][j].tick == tick) {
        if (j < midifile[0].size() - 1 && midifile[0][j+1].tick == tick) {
          continue; // Keep moving until we get to the last note at the tick
        }
        regionSize.push_back(j - previousEventIndex);
        previousEventIndex = j;
        break;
      }
    }
  }

  cout << "TOTAL " << midifile[0].size() << endl;
  int maxRegion = 0;
  for (auto region : regionSize) {
    if (region > maxRegion) {
      maxRegion = region;
    }
    cout << "REE " << region << endl;
  }

  unsigned fileDuration = midifile.getFileDurationInTicks();
  for (int j = 0; j < regionSize.size(); j++) {
    int tick = j * fileDuration/regionSize.size();
    cout << j * fileDuration/regionSize.size();
    cout << j << " Adding " << maxRegion - regionSize[j] << " notes at tick " << tick << endl;
    for (int i = regionSize[j]; i < maxRegion; i++) {
      // Add useless midi events to balance the file
      midifile.addNoteOff(0, tick, 0, 0);
    }
  }
  midifile.sortTracks();

  cout << "TOTAL " << midifile[0].size() << endl;

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    MidiEvent* me;
    #pragma omp for
    for (int i = 0; i < midifile[0].size() - 1; i++) {
      me = &midifile[0][i];  
      me->isNoteOn() ? osc[id].start() : osc[id].stop();
      if (me->isNote()) {
        osc[id].setNote(me->getKeyNumber());
        osc[id].setGain(0.5 * (((double) me->getVelocity())/127.0));
      }
      
      thread_sleep((midifile[0][i + 1].tick - me->tick) * secondsPerTick * 1000);
    }
  }
  
  return 0;
}
