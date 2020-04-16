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
class Delay : public Effect, public ParameterManager {
  public:
    Delay() :
      ParameterManager({
                        { .name="Delay", .min=0.0, .max=5.0, .defaultValue=1.0 },
                        { .name="Feedback", .min=0.0, .max=1.0, .defaultValue=0.5 }
        }) {};
    enum Parameters {
                     DELAY=0,
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
