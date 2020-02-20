#ifndef LADSPAMANAGER_H
#define LADSPAMANAGER_H

#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <ladspa.h>
#include <vector>

namespace tsal {

typedef std::pair<std::string, std::string> ladspa_key;
class LadspaManager {
  public:
    std::vector<ladspa_key> listPlugins();
    const LADSPA_Descriptor * loadPlugin(const std::string& pluginPath);
};

}

#endif
