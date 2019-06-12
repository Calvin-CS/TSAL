#include "MidiFile.h"
#include <algorithm>

#ifndef MIDIPARSER_H
#define MIDIPARSER_H

namespace tsal {

class MidiParser {
  public:
    void setNumThreads(unsigned threads) { mNumThreads = threads; };
    void read(const std::string& filename);
    const smf::MidiEvent& operator[] (int aEvent) const;
		smf::MidiEvent& operator[] (int aEvent);
    unsigned size() { return mMidiFile[0].size(); };
    double ticksToMs(unsigned ticks) const;
    double quaterNoteMs(unsigned ticks) const;
  private:
    double mMsPerTick;
    double mMsPerQuater;
    unsigned mNumThreads = 1; 
    smf::MidiFile mMidiFile; 
};

}

#endif
