#include "RtAudio.h"
#include "AudioNode.h"
#include "Compressor.h"

#ifndef TSAUDIO_H
#define TSAUDIO_H

namespace tsal {

/** @class TSAudio
 * @brief The main audio manager that handles the overhead of audio buffers, audio nodes,
 * and sampling
 * 
 * To use TSAL, the TSAudio class needs to be initiliazed at the start of the project.
 * All other audio nodes will be routed through TSAudio
 */
class TSAudio : public AudioNode {
  public:
    TSAudio();
    /**
     * @brief Construct a new TSAudio object
     * 
     * @param channels number of channels, ex: 1 = mono, 2 = stereo
     * @param sampleRate if left blank, TSAudio will default to the highest sample rate supported
     */
    TSAudio(unsigned channels, unsigned sampleRate);

    ~TSAudio();

    void addNode(AudioNode* node) {
      mCompressor.addNode(node);
    }

    void removeNode(AudioNode* node) {
      mCompressor.removeNode(node);
    }
  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mChannels;
    Compressor mCompressor;
};

}
#endif
