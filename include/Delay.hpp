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
    virtual void setMixer(Mixer* mixer) override;
    virtual double getOutput() override;
    void setDelay(unsigned delay);
    void setFeedback(double feedback);
  private:
    std::unique_ptr<Buffer<double>> mBuffer = nullptr;
    unsigned mCounter = 0;
    unsigned mDelay = 0;
    double mFeedback = 0.5;

    Util::ParameterRange<unsigned> mDelayRange;
    static Util::ParameterRange<double> mFeedbackRange;
};

}
#endif
