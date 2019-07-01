#include "MidiSequencer.hpp"
#include "Mixer.hpp"

namespace tsal {

void MidiSequencer::tick() {
  // This has some margin of error since mSamplesPerTick is a floating point number
  // But it seems to work well enough, maybe in the future it would be better to change to a more consistent timing method
  if (++mSampleTime > mSamplesPerTick) {
    mTick++;
    //if (mTickEvents.size() > 0 && (mTickEvents[mTickEvents.back()] <= mTick || mTickEvents[mTickEvents.back()] >= mTick)) {
    for (unsigned i = 0; i < mTickEvents.size(); i++) {
      if (mTick >= mTickEvents[i]) {
        mTickEvents.erase(mTickEvents.begin() + i);
        cond.notify_all();
      } 
    }
    mSampleTime = 0;
  }
}

void MidiSequencer::setBPM(unsigned bpm) {
  mBPM = bpm;
  setSamplesPerTick();
}

void MidiSequencer::setPPQ(unsigned ppq) {
  mPPQ = ppq;
  setSamplesPerTick();
}

void MidiSequencer::setSamplesPerTick() {
  mSamplesPerTick = Mixer::getSampleRate() / ((mBPM * mPPQ) / 60);
}

unsigned MidiSequencer::getTick() const {
  return mTick;
}

void MidiSequencer::waitForTick(unsigned tick) {
  mTickEvents.push_back(tick);
  std::unique_lock<std::mutex> lk(mutex);
  cond.wait(lk, [this, tick]{return mTick >= tick;}); 
}


}
