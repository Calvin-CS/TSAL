#include "MidiSequencer.hpp"
#include "Mixer.hpp"

namespace tsal {

void MidiSequencer::tick() {
  if (++mSampleTime == mSamplesPerTick) {
    mTick++;
    mSampleTime = 0;
  }
}

void MidiSequencer::setBPM(unsigned bpm) {
  std::cout << bpm << std::endl;
}


}
