#include <iostream>
#include <vector>

typedef signed short BIT_DEPTH;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

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
    virtual double nextBufferSample() { return 0; };

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
     * @brief Set active status of an object
     * 
     * The implementation details of active are deferred to the child
     * 
     * @param active 
     */
    void setActive(bool active) {
      mActive = active;
    }

  protected:
    bool mActive = true;

    static unsigned mSampleRate;
    static unsigned mBufferFrames;
};

}
#endif
