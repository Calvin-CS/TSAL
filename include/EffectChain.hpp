#ifndef EFFECTCHAIN_H
#define EFFECTCHAIN_H

#include "RouteDevice.hpp"
#include "OutputDevice.hpp"
#include "Instrument.hpp"
#include "Effect.hpp"
namespace tsal {

class EffectChain : public OutputDevice {
  public:
    void setInput(OutputDevice& input);
    virtual double getOutput() override;
    virtual void setMixer(Mixer* mixer) override;
    void add(Effect& effect);
    void remove(Effect& effect);
    int size() { return mEffects.size(); };
  private:
    std::vector<Effect*> mEffects;
    OutputDevice* mInput;
};

}

#endif
