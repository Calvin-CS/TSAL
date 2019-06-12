#include "MidiParser.h"
#include <iostream>

namespace tsal {

void MidiParser::read(const std::string& filename) {
  mMidiFile.read(filename);
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
  std::cout << mMsPerQuater << std::endl;
}

double MidiParser::ticksToMs(unsigned ticks) const {
  return ticks * mMsPerTick;
}

double MidiParser::quaterNoteMs(unsigned ticks) const {
  return ticks * mMsPerQuater;
}
const smf::MidiEvent& MidiParser::operator[] (int aEvent) const {
  return mMidiFile[0][aEvent];
}

smf::MidiEvent& MidiParser::operator[] (int aEvent) {
  return mMidiFile[0][aEvent];
}

} 
