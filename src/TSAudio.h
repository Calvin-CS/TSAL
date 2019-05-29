#include "RtAudio.h"
#include "AudioNode.h"

#ifndef TSAUDIO_H
#define TSAUDIO_H

/** \class TSAudio
 * \brief The main audio manager that handles the overhead of audio buffers, audio nodes,
 * and sampling
 * 
 * To use TSAL, the TSAudio class needs to be initiliazed at the start of the project.
 * All other audio nodes will be routed through TSAudio
 */
class TSAudio {
  public:
    TSAudio();
    /**
     * \brief Construct a new TSAudio object
     * 
     * \param channels number of channels, ex: 1 = mono, 2 = stereo
     * \param sampleRate if left blank, TSAudio will default to the highest sample rate supported
     */
    TSAudio(unsigned channels, unsigned sampleRate);

    ~TSAudio();

    /** 
     * \brief Get all the samples from the audio nodes and outputs to a buffer
     */
    double getBufferSamples();

    /**
     * \brief Add an audio node to be for generating sound
     * 
     * \param node 
     */
    void addNode(AudioNode* node) { mAudioNodes.push_back(node); };
    /**
     * \brief Remove an audio node
     * 
     * \param node 
     */
    void removeNode(AudioNode* node);
    
  private:
    void initalizeStream();
    RtAudio mRtAudio;
    unsigned mSampleRate = 0;
    unsigned mChannels;

    std::vector<AudioNode*> mAudioNodes;
};

#endif
