#include "Amp.hpp"

namespace tsal {

ParameterManager::Parameter Amp::AmpParameterVolume = { .name="Volume", .min=0.0, .max=2.0, .defaultValue=1.0 };

}
