#include "RtAudio.h"
#include "InputDevice.h"
#include "OutputDevice.h"
#include "Compressor.h"
#include "Channel.h"

#ifndef MIXER_H
#define MIXER_H

namespace tsal {

/** @class Mixer
 * @brief The main audio manager that handles the overhead of audio buffers 
 * and channel mixing
 * 
 * To use TSAL, the TSAudio class needs to be initiliazed at the start of the project.
 * All other audio nodes will be routed through TSAudio
 */
class Mixer : public InputDevice, private OutputDevice {
  public:
    Mixer();
    Mixer(unsigned sampleRate);
    ~Mixer();
    void add(Channel* channel);
    void add(Instrument* instrument);
  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mChannels;
    Channel mMaster;
    Compressor mCompressor;
};

}
#endif
