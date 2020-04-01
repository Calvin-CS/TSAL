#ifndef LADSPAMANAGER_H
#define LADSPAMANAGER_H

#include "AudioBuffer.hpp"
#include <iostream>
#include <sstream>
#if defined(__GNUC__) // GNU compiler
#include <dlfcn.h>
#endif
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
    static std::vector<ladspa_key> listPlugins();
    static const LADSPA_Descriptor* loadPlugin(const std::string& pluginPath);
};

}

#endif
