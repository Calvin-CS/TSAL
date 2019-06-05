#include <iostream>

#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

namespace tsal {

class OutputDevice {
  public:
    virtual ~OutputDevice() {};
    virtual double getOutput() { return 0.0; };
    virtual void setActive(bool active) { mActive = active; };
  protected:
    bool mActive = true;
    static unsigned mSampleRate;
    static unsigned mBufferFrames;
};

};

#endif
