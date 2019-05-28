#ifndef AUDIONODE_H
#define AUDIONODE_H

class AudioNode {
  public:
    virtual double getBufferSample() { return 0; };
};

#endif
