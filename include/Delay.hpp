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
    Delay();
    virtual double getOutput() override;
    void setDelay(unsigned delay);
    void setFeedback(double feedback);
  private:
    std::unique_ptr<Buffer<double>> mBuffer;
    unsigned mCounter = 0;
    unsigned mDelay = 48000;
    double mFeedback = 0.5;

    ParameterRange<unsigned> mDelayRange;
    static ParameterRange<double> mFeedbackRange;
};

}
#endif
