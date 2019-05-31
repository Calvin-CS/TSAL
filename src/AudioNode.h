#include <iostream>
#include <vector>

#ifndef AUDIONODE_H
#define AUDIONODE_H

namespace tsal {
  
/** @class AudioNode
 * @brief Base class for audio nodes
 * 
 * AudioNode is the basic structure for nodes handled by TSAudio
 */
class AudioNode {
  public:
    virtual ~AudioNode() {};
    /**
     * @brief Get an audio sample for the audio buffer
     * 
     * Used by TSAudio to get samples of sound
     * 
     * @return double the audio sample
     */
    virtual double nextBufferSample() { return getNodeSamples(); };

    /**
     * @brief Add an audio node to be for generating sound
     * 
     * @param node 
     */
    void addNode(AudioNode* node);

    /**
     * @brief Remove an audio node
     * 
     * @param node 
     */
    void removeNode(AudioNode* node);

    /**
     * @brief Get the combined audio sample of child nodes
     * 
     * @return double the sample
     */
    double getNodeSamples();

  protected:
    static unsigned mSampleRate;
    static unsigned mBufferFrames;
    std::vector<AudioNode*> mAudioNodes;
};

}
#endif
