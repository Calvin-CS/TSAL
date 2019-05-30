#include "AudioNode.h"

AudioNode::~AudioNode() {
  for (unsigned i = 0; i < mAudioNodes.size(); i++) {
    delete mAudioNodes[i];
  }
}

double AudioNode::getNodeSamples() {
  double sample = 0.0;

  for (unsigned i = 0; i < mAudioNodes.size(); i++)
    sample += mAudioNodes[i]->nextBufferSample();

  return sample;
}

void AudioNode::addNode(AudioNode* node) {
  mAudioNodes.push_back(node);
}

void AudioNode::removeNode(AudioNode* node) {
  for (std::vector<AudioNode*>::iterator it = mAudioNodes.begin(); it != mAudioNodes.end(); ++it) {
    if (node == *it) {
      mAudioNodes.erase(it);
    }
  }
}
