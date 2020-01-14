#ifndef MIXER_H
#define MIXER_H

#include "OutputDevice.hpp"
#include "Channel.hpp"
#include "Context.hpp"
#include "Compressor.hpp"
#include "Sequencer.hpp"
#include "portaudio.h"
#include <memory>
#include <condition_variable>
#include <mutex>

namespace tsal {

/** @class Mixer
 * @brief The main audio manager that handles the overhead of audio buffers 
 * and channel mixing
 * 
 * To use TSAL, the Mixer class needs to be initiliazed at the start of the project.
 * All other audio devices will be routed through the Mixer's master channel
 */
class Mixer {
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

    const Context& getContext() { return mContext; };

    void requestModelChange(std::function<void()> change);
    void runModelChanges();

  private:
    unsigned mChangeRequests = 0;
    std::mutex mChangeRequestMutex;
    std::mutex mModelMutex; 
    std::mutex mWaitModelChangeMutex;
    std::condition_variable mWaitModelChangeCondition;
    std::condition_variable mModelChangeRequestCondition;
    Context mContext;
    Channel mMaster;
    Compressor mCompressor;
    Sequencer mSequencer;
    PaStream *mPaStream;
    void openPaStream();
    
    AudioBuffer<float> mBuffer;
    int audioCallback(float *outputBuffer, unsigned long frameCount);
    static void paStreamFinished(void* userData);
    static int paCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );
    
};

}
#endif
