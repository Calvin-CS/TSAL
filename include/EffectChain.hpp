#ifndef EFFECTCHAIN_H
#define EFFECTCHAIN_H

#include "OutputDevice.hpp"
#include "Effect.hpp"
namespace tsal {

/** @class EffectChain
 * @brief Manages the effect chain for a channel
 *
 * Effects are applied to a channel linked in a chain and updating the audio 
 * stream as it passes through the chain
 */
class EffectChain : public OutputDevice {
  public:
    EffectChain(Mixer* mixer, OutputDevice& output) : OutputDevice(mixer), mInput(output) {};
    ~EffectChain();
    virtual double getOutput() override;
    virtual void getOutput(std::vector<float>& buffer, unsigned long frameCount, unsigned channelCount) override;
    virtual void setMixer(Mixer* mixer) override;
    void add(Effect& effect);
    void remove(Effect& effect);
    int size() { return mEffects.size(); };
  private:
    void lock() { std::lock_guard<std::mutex> guard(mVectorMutex); };
    std::vector<Effect*> mEffects;
    OutputDevice& mInput;
    std::mutex mVectorMutex;
};

}

#endif
