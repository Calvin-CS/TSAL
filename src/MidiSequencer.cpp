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
        mEventCondition.notify_all();
      } 
    }
    mSampleTime = 0;
  }
}

void MidiSequencer::setTick(unsigned tick) {
  mTick = tick;
}

/**
 * @brief Set the BPM (beats pre minute)
 * 
 * @param bpm 
 */
void MidiSequencer::setBPM(unsigned bpm) {
  mBPM = bpm;
  setSamplesPerTick();
}

/**
 * @brief Set the PPQ (pulses per quater)
 * 
 * @param ppq 
 */
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

/**
 * @brief Put a thread to sleep for the given tick time
 * 
 * @param tick 
 */
void MidiSequencer::waitForTick(unsigned tick) {
  // We are potentionally adding to this vector from multiple threads so make sure it's thread safe
  // We have to block this or else the guard waits till the thread is done sleeping to release the mutex
  {
    std::lock_guard<std::mutex> guard(mVectorMutex); 
    mTickEvents.push_back(tick);
  }
  
  std::unique_lock<std::mutex> lk(mEventMutex);
  mEventCondition.wait(lk, [this, tick]{return mTick >= tick;}); 
}


}
