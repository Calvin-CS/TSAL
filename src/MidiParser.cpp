#include "MidiParser.h"
#include <iostream>

namespace tsal {

/**
 * @brief Construct a new MidiParser
 * 
 */
MidiParser::MidiParser() {
  setNumThreads(1);
}

/**
 * @brief Construct a new MidiParser 
 * 
 * @param threads 
 */
MidiParser::MidiParser(unsigned threads) {
  setNumThreads(threads);
}

/**
 * @brief Construct a new MidiParser and reads in a midi file
 * 
 * @param threads 
 * @param filename 
 */
MidiParser::MidiParser(unsigned threads, const std::string& filename) {
  setNumThreads(threads);
  read(filename);
}

/**
 * @brief Read a midi file from disk
 * 
 * A midi file is read and parsed by the midifile library. Useless events are also added 
 * to the events stored in memory so that portions of the song can be equally processed
 * by the number of threads previously specified
 * 
 * @param filename 
 */
void MidiParser::read(const std::string& filename) {
  mMidiFile.read(filename);
  mHasRead = true;
  mMidiFile.joinTracks();

  smf::MidiEventList midiTrack = mMidiFile[0];

  std::vector<unsigned> eventRegions;
  int previousRegionBound = 0;
  int totalTicks = mMidiFile.getFileDurationInTicks();
  for (unsigned i = 0; i < mNumThreads; i++) {
    // Set the new bound for the region
    int tick = (i + 1) * totalTicks/mNumThreads;
    for (int j = 0; j < midiTrack.size(); j++) {
      if (midiTrack[j].tick == tick) {
        if (j < midiTrack.size() - 1 && midiTrack[j + 1].tick == tick) {
          continue;
        }
        eventRegions.push_back(j - previousRegionBound);
        previousRegionBound = j;
        break;
      }
    }
  }

  unsigned maxRegion = *std::max_element(eventRegions.begin(), eventRegions.end());
  for (unsigned i = 0; i < eventRegions.size(); i++) {
    int tick = i * totalTicks/eventRegions.size();
    for (unsigned j = eventRegions[i]; j < maxRegion; j++) {
      mMidiFile.addNoteOff(0, tick, 0, 0);
    }
  }

  mMidiFile.sortTracks();
  mMsPerTick = 1000 * mMidiFile.getFileDurationInSeconds()/((double) totalTicks);
  mMsPerQuater = 1000 * mMidiFile.getFileDurationInSeconds()/((double) mMidiFile.getFileDurationInQuarters());
}

/**
 * @brief Convert midi ticks into milliseconds based on midi file
 * 
 * @param ticks 
 * @return double 
 */
double MidiParser::ticksToMs(unsigned ticks) const {
  if (!mHasRead) {
    std::cout << "MidiParser: No file has been read" << std::endl;
  }
  return ticks * mMsPerTick;
}

/**
 * @brief Convert quarter notes into milliseconds based on midi file 
 * 
 * @param ticks 
 * @return double 
 */
double MidiParser::quaterNoteMs(unsigned ticks) const {
  if (!mHasRead) {
    std::cout << "MidiParser: No file has been read" << std::endl;
  }
  return ticks * mMsPerQuater;
}

/**
 * @brief Get a MidiEvent
 * 
 * @param aEvent 
 * @return const smf::MidiEvent& 
 */
const smf::MidiEvent& MidiParser::operator[] (int aEvent) const {
  return mMidiFile[0][aEvent];
}

/**
 * @brief Set a MidiEvent
 * 
 * @param aEvent 
 * @return smf::MidiEvent& 
 */
smf::MidiEvent& MidiParser::operator[] (int aEvent) {
  return mMidiFile[0][aEvent];
}

} 
