#ifndef MIDIPARSER_H
#define MIDIPARSER_H

#include "MidiFile.h"
#include <algorithm>

namespace tsal {

/** @class MidiParser 
 * @brief Parse a midi file for the sake of multithreading playing
 * 
 * Midi files are composed of midi events such as note on and note off. The midifile library
 * parses the file and extracts these messages into objects. The goals of TSAL are to 
 * audiolize multithreading with sound. One example is processing a midi file. Instead of using different
 * tracks, TSAL overlays sound with multiple threads by reading different portions of a midi file.
 * If a midi file is prepared with this process in mind, one track can contain multiple parts by
 * partitioning equally across the length of the track. To make the use of this concept more felxible, 
 * MidiParser ensures that the number of midi events are equally distributed so that this process can
 * be easily performed. It simply adds useless midi events where necessary based upon the number of threads
 * specified
 *  
 */
class MidiParser {
  public:
    MidiParser();
    MidiParser(unsigned threads);
    MidiParser(unsigned threads, const std::string& filename);
    void setNumThreads(unsigned threads) { mNumThreads = threads; };
    void read(const std::string& filename);
    const smf::MidiEvent& operator[] (int aEvent) const;
		smf::MidiEvent& operator[] (int aEvent);
    unsigned size() { return mMidiFile[0].size(); };
    unsigned getPPQ() const { return mMidiFile.getTicksPerQuarterNote(); };

  private:
    bool validPath(const std::string& filename); 
    double mMsPerTick = 0.0;
    double mMsPerQuater = 0.0;
    unsigned mNumThreads = 1;
    bool mHasRead = false; 
    smf::MidiFile mMidiFile; 
};

}

#endif
