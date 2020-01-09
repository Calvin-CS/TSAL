#ifndef DELAY_H
#define DELAY_H

#include "Effect.hpp"
#include "Buffer.hpp"
#include "Util.hpp"

namespace tsal {

/** @class Delay
 * @brief A delay effect
 * 
 * Adds a delay effect to audio input to achieve a more spacious sound
 */
class Delay : public Effect {
  public:
    Delay(const Context& context);
    void init();
    virtual void setMixer(Mixer* mixer) override;
    virtual void getOutput(AudioBuffer<float> &buffer) override;
    void setDelay(unsigned delay);
    void setFeedback(double feedback);
  private:
    Buffer<double> mBuffer;
    unsigned mCounter = 0;
    int mDelay = 0;
    double mFeedback = 0.5;

    Util::ParameterRange<unsigned> mDelayRange;
    static Util::ParameterRange<double> mFeedbackRange;
};

}
#endif
