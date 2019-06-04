#include <iostream>

#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

namespace tsal {

class OutputDevice {
  public:
    virtual double getOutput() { return 0.0; };
  protected:
    static unsigned mSampleRate;
    static unsigned mBufferFrames;
};

};

#endif
