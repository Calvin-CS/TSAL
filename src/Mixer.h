#include "RtAudio.h"
#include "InputDevice.h"
#include "OutputDevice.h"
#include "Channel.h"
#include "Compressor.h"

#ifndef MIXER_H
#define MIXER_H

namespace tsal {

/** @class Mixer
 * @brief The main audio manager that handles the overhead of audio buffers 
 * and channel mixing
 * 
 * To use TSAL, the Mixer class needs to be initiliazed at the start of the project.
 * All other audio devices will be routed through the Mixer
 */
class Mixer : public InputDevice, private OutputDevice {
  public:
    Mixer();
    Mixer(unsigned sampleRate);
    ~Mixer();
    void add(Channel* channel);
    void remove(Channel* channel);
    void add(Instrument* instrument);
    void remove(Instrument* instrument);

    static unsigned getSampleRate() { return mSampleRate; };
    static unsigned getBufferFrames() { return mBufferFrames; };
    virtual double getInput() override;
  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mChannels;
    Channel mMaster;
    Compressor mCompressor;

    static unsigned mSampleRate;
    static unsigned mBufferFrames;
};

}
#endif
