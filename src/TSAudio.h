#include "RtAudio.h"
#include "AudioNode.h"

#ifndef TSAUDIO_H
#define TSAUDIO_H

class TSAudio {
  public:
    TSAudio();
    TSAudio(unsigned channels, unsigned sampleRate);
    ~TSAudio();
    double getBufferSamples();
    void addNode(AudioNode* node) { mAudioNodes.push_back(node); };
    void removeNode(AudioNode* node);
    
  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mSampleRate = 0;
    unsigned mChannels;

    std::vector<AudioNode*> mAudioNodes;
};

#endif
