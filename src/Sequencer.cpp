#include "Sequencer.hpp"
#include "Mixer.hpp"

namespace tsal {

void Sequencer::tick() {
  // This has some margin of error since mSamplesPerTick is a floating point number
  // But it seems to work well enough, maybe in the future it would be better to change to a more consistent timing method
  if (++mSampleTime > mSamplesPerTick) {
    mTick++;
    // if (mTickEvents.size() > 0 && (mTickEvents[mTickEvents.back()] <= mTick || mTickEvents[mTickEvents.back()] >= mTick)) {
    for (unsigned i = 0; i < mTickEvents.size(); i++) {
      if (mTick >= mTickEvents[i]) {
        mTickEvents.erase(mTickEvents.begin() + i);
        mCondition.notify_all();
      } 
    }
    // Ugly replace soon
    for (unsigned i = 0; i < mEvents.size(); i++) {
      if (mTick >= mEvents[i]->tick) {
        mEvents[i]->callback();
        mEvents.erase(mEvents.begin() + i);
      }
    }
    mSampleTime = 0;
  }
}

void Sequencer::setTick(unsigned tick) {
  mTick = tick;
}

/**
 * @brief Set the BPM (beats pre minute)
 * 
 * @param bpm 
 */
void Sequencer::setBPM(unsigned bpm) {
  mBPM = Util::checkParameterRange("Sequencer: BPM", bpm, mBPMRange);
  setSamplesPerTick();
}

/**
 * @brief Set the PPQ (pulses per quater)
 * 
 * @param ppq 
 */
void Sequencer::setPPQ(unsigned ppq) {
  mPPQ = Util::checkParameterRange("Sequencer: PPQ", ppq, mPPQRange);
  setSamplesPerTick();
}

void Sequencer::setSamplesPerTick() {
  mSamplesPerTick = mSampleRate / ((mBPM * mPPQ) / 60);
}

void Sequencer::schedule(std::function<void ()> callback, NoteScale scale, unsigned duration) {
  int tick = getTicksInNote(scale) * duration;
  mEvents.push_back(std::make_unique<Event>(Event(mTick + tick, callback)));
}

unsigned Sequencer::getTick() const {
  return mTick;
}

unsigned Sequencer::getTicksInNote(NoteScale note) const {
  return (note == TICK) ? 1 : mPPQ * 4.0 * (1.0/note);
}

/**
 * @brief Put a thread to sleep for the given tick time
 * 
 * @param tick 
 */
void Sequencer::waitForTick(unsigned tick) {
  std::unique_lock<std::mutex> lk(mMutex);
  mTickEvents.push_back(tick);
  mCondition.wait(lk, [this, tick]{return mTick >= tick;}); 
}

Util::ParameterRange<unsigned> Sequencer::mBPMRange = std::make_pair(1, 1000);
Util::ParameterRange<unsigned> Sequencer::mPPQRange = std::make_pair(1, 1000);

}
