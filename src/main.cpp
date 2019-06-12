#include "Oscillator.h"
#include "Chord.h"
#include "Mixer.h"
#include "MidiNotes.h"
#include "Compressor.h"
#include "Channel.h"
#include "MidiParser.h"
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
unsigned numThreads = 4;

int main() {  
  Mixer mixer;
  vector<Oscillator> osc(numThreads); 
  for (unsigned i = 0; i < osc.size(); i++) {
    osc[i].setGain(0.05);
    mixer.add(&osc[i]);
  }
    
  MidiParser midiParser;
  midiParser.setNumThreads(1);
  midiParser.read("/home/mark/Downloads/jub.mid");

  omp_set_num_threads(numThreads);
  /*
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    thread_sleep(id * midiParser.quaterNoteMs(4));
    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto me = midiParser[i];  
      if (me.isNoteOn()) {
        osc[id].start();
        osc[id].setNote(me.getKeyNumber());
        //osc[id].setGain(0.5 * (((double) me.getVelocity())/127.0));
      }
      
      thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
    }
  }
  */
  /*
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    #pragma omp for
    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto me = midiParser[i];  
      me.isNoteOn() ? osc[id].start() : osc[id].stop();
      if (me.isNote()) {
        osc[id].setNote(me.getKeyNumber());
        osc[id].setGain(0.5 * (((double) me.getVelocity())/127.0));
      }
      
      thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
    }
  }
  */
  for (unsigned i = 0; i < osc.size(); i++) {
  }
  return 0;
}
