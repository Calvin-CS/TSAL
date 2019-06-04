#include "Effect.h"

namespace tsal {

void Effect::add(Effect* effect) {
  InputDevice::add(effect);
}

void Effect::remove(Effect* effect) {
  InputDevice::remove(effect);
}

};
