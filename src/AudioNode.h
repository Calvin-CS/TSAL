#ifndef AUDIONODE_H
#define AUDIONODE_H

/** \class AudioNode
 * \brief Base class for audio nodes
 * 
 * AudioNode is the basic structure for nodes handled by TSAudio
 */
class AudioNode {
  public:
    /**
     * \brief Get an audio sample for the audio buffer
     * 
     * Used by TSAudio to get samples of sound
     * 
     * \return double the audio sample
     */
    virtual double nextBufferSample() { return 0; };
};

#endif
