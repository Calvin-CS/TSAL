#include "RtAudio.h"
#include "InputDevice.h"
#include "OutputDevice.h"
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
class Mixer : public InputDevice, private OutputDevice {
  public:
    Mixer();
    /**
     * @brief Construct a new TSAudio object
     * 
     * @param sampleRate if left blank, TSAudio will default to the highest sample rate supported
     */
    Mixer(unsigned sampleRate);

    ~Mixer();

  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mChannels;
    //Compressor mCompressor;
};

}
#endif
