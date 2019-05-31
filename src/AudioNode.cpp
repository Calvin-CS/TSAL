#include <iostream>
#include <algorithm>
#include "AudioNode.h"

namespace tsal {

double AudioNode::getNodeSamples() {
  double sample = 0.0;

  // Get combined sample of all children nodes
  for (unsigned i = 0; i < mAudioNodes.size(); i++) {
    sample += mAudioNodes[i]->nextBufferSample();
  }

  return sample;
}

void AudioNode::addNode(AudioNode* node) {
  mAudioNodes.push_back(node);
}

void AudioNode::removeNode(AudioNode* node) {
  mAudioNodes.erase(std::remove(mAudioNodes.begin(), mAudioNodes.end(), node));
}

// Set the sampleRate to zero and let the TSAudio object handle it
unsigned AudioNode::mSampleRate = 0;

}
