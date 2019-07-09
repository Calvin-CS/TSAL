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
        mCondition.notify_all();
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
  mBPM = checkParameterRange("MidiSequencer: BPM", bpm, mBPMRange);
  setSamplesPerTick();
}

/**
 * @brief Set the PPQ (pulses per quater)
 * 
 * @param ppq 
 */
void MidiSequencer::setPPQ(unsigned ppq) {
  mPPQ = checkParameterRange("MidiSequencer: PPQ", ppq, mPPQRange);
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
  std::unique_lock<std::mutex> lk(mMutex);
  mTickEvents.push_back(tick);
  mCondition.wait(lk, [this, tick]{return mTick >= tick;}); 
}

ParameterRange<unsigned> MidiSequencer::mBPMRange = std::make_pair(1, 1000);
ParameterRange<unsigned> MidiSequencer::mPPQRange = std::make_pair(1, 1000);

}
