#ifndef LADSPAMANAGER_H
#define LADSPAMANAGER_H

#include "AudioBuffer.hpp"
#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <ladspa.h>
#include <vector>

namespace tsal {

typedef std::pair<std::string, std::string> ladspa_key;

class LadspaManager {
  public:
    struct Port {
        Port(unsigned portId) : id(portId) {}
        AudioBuffer<LADSPA_Data> buffer;
        unsigned id;
    };
    std::vector<ladspa_key> listPlugins();
    const LADSPA_Descriptor * loadPlugin(const std::string& pluginPath);
};

}

#endif
