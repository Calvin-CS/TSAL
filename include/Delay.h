#include "Effect.h"
#include "Buffer.h"
#include "Util.h"

#ifndef DELAY_H
#define DELAY_H

// Calculate this dynamically at runtime
#define DELAY_MAX_BUFFER 96000 * 2
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
    Buffer<double> mBuffer;
    unsigned mCounter = 0;
    unsigned mDelay = 48000;
    double mFeedback = 0.5;

    static ParameterRange<unsigned> mDelayRange;
    static ParameterRange<double> mFeedbackRange;
};

}
#endif
