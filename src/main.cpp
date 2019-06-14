#include "Oscillator.h"
#include "Chord.h"
#include "Mixer.h"
#include "MidiNotes.h"
#include "Compressor.h"
#include "Delay.h"
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
unsigned numThreads = 1;

int main() {  
  Mixer mixer;
  Channel chan;
  Delay delay;
  chan.add(delay);
  vector<Oscillator> osc(numThreads); 
  for (unsigned i = 0; i < osc.size(); i++) {
    osc[i].setActive(false);
    osc[i].setGain(0.05);
    if (i == 2)
      osc[i].setGain(0.01);
    chan.add(osc[i]);
  }
    
  mixer.add(chan);
  //chan.remove(delay);

  MidiParser midiParser(1, "/home/mark/Downloads/velocity.mid");

  omp_set_num_threads(numThreads);
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    thread_sleep(id * midiParser.quaterNoteMs(4));
    osc[id].setActive();
    for (unsigned i = 0; i < midiParser.size() - 1; i++) {
      auto me = midiParser[i];  
      if (me.isNoteOn()) {
        osc[id].playNote(me.getKeyNumber() + (id == 2 ? 12 : 0), me.getVelocity());
      }
      
      thread_sleep(midiParser.ticksToMs(midiParser[i + 1].tick - me.tick));
      osc[id].stop();
    }
  }
  thread_sleep(1000);
  /*
  #pragma omp par 
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
    mixer.remove(osc[i]);
  }
  return 0;
}
