#include "Panning.hpp"

namespace tsal {

ParameterManager::Parameter Panning::PanningParameter = { .name="Panning", .min=-1.0, .max=1.0, .defaultValue=0.0 };

void Panning::setChannelPanning(unsigned channelCount) {
  switch (channelCount) {
    // mono channel
  case 1: {
    mChannelPanning.resize(1);
    mChannelPanning[0] = 1.0 - std::abs(mPanning);
    break;
  }
    // stereo channel
  case 2: {
    const double delta = mPanning * M_PI/4.0;
    mChannelPanning.resize(2);
    const auto s = sin(delta);
    const auto c = cos(delta);
    mChannelPanning[0] = panningConstant * (c + s);
    mChannelPanning[1] = panningConstant * (c - s);
    break;
  }
  }
};

double Panning::panningConstant = std::sqrt(2.0)/2.0;

}
