#ifndef DELAY_H
#define DELAY_H

#include "AudioBuffer.hpp"
#include "ParameterManager.hpp"
#include "Effect.hpp"
#include "Util.hpp"
#include <vector>

namespace tsal {

/** @class Delay
 * @brief A delay effect
 * 
 * Adds a delay effect to audio input to achieve a more spacious sound
 */
class Delay : public Effect {
  public:
    Delay() :
      Effect(DelayParameters) {};
    Delay(std::vector<Parameter> parameters) :
      Effect(DelayParameters) {
      addParameters(parameters);
    };
    static std::vector<Parameter> DelayParameters;
    enum Parameters {
                     WET_DRY=0,
                     DELAY,
                     FEEDBACK,
    };
    virtual void updateContext(const Context& context) override;
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void setDelay(double delay);
    void setFeedback(double feedback);
  protected:
    virtual void parameterUpdate(unsigned id) override;
  private:
    AudioBuffer<float> mBuffer;
    unsigned mCounter = 0;
    unsigned mDelayFrames = 0;
};

}
#endif
