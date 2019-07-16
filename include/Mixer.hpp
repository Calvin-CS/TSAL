#ifndef MIXER_H
#define MIXER_H

#include "InputDevice.hpp"
#include "OutputDevice.hpp"
#include "Channel.hpp"
#include "Compressor.hpp"
#include "MidiSequencer.hpp"
#include <rtaudio/RtAudio.h>


typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

namespace tsal {

/** @class Mixer
 * @brief The main audio manager that handles the overhead of audio buffers 
 * and channel mixing
 * 
 * To use TSAL, the Mixer class needs to be initiliazed at the start of the project.
 * All other audio devices will be routed through the Mixer
 */
class Mixer : public InputDevice {
  public:
    Mixer();
    Mixer(unsigned sampleRate);
    ~Mixer();

    void add(Channel& channel);
    void add(Instrument& instrument);
    void add(Effect& effect);

    void remove(Channel& channel);
    void remove(Instrument& instrument);
    void remove(Effect& effect);

    Channel& getMaster() { return mMaster; };
    MidiSequencer& getSequencer() { return mSequencer; };
    unsigned getSampleRate() { return mSampleRate; };
    unsigned getCurrentTick() { return mCurrentTick; };
    unsigned getBufferFrames() { return mBufferFrames; };

    virtual double getInput() override;

  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mChannels;
    Channel mMaster;
    Compressor mCompressor;
    MidiSequencer mSequencer;
    
    unsigned mCurrentTick = 0;
    unsigned mSampleRate = 0;
    unsigned mBufferFrames = 0;
    static void errorCallback(RtAudioError::Type type, const std::string &errorText);
    static int streamCallback(void *outputBuffer,
                      __attribute__((unused)) void *inputBuffer,
                      unsigned nBufferFrames, 
                      __attribute__((unused)) double streamTime,
                      RtAudioStreamStatus status,
                      void *data);
};

}
#endif
