#include "LadspaManager.hpp"

namespace tsal {

std::vector<ladspa_key> LadspaManager::listPlugins() {
  // std::vector<std::string> ladspaDirectories;
  // std::istringstream ladspaEnv(getenv("LADSPA_PATH"));
  // std::string s;
  // while (std::getline(ladspaEnv, s, ':')) {
  //   std::cout << s << std::endl;
  //   ladspaDirectories.push_back(s);
  // }
  std::vector<ladspa_key> ladspa_keys;
  return ladspa_keys;
}

const LADSPA_Descriptor * LadspaManager::loadPlugin(const std::string& pluginPath) {
  const LADSPA_Descriptor * descriptor = NULL;
  /*
  void * pluginHandle = dlopen(pluginPath.c_str(), RTLD_NOW);
  if (pluginHandle == NULL) {
    std::cout << "Failed to open plugin: " << pluginPath << std::endl;
    
  }
  
  LADSPA_Descriptor_Function descriptorFunction = (LADSPA_Descriptor_Function)dlsym(pluginHandle, "ladspa_descriptor");

  for (long pluginIndex = 0;; pluginIndex++) {
    descriptor = descriptorFunction(pluginIndex);
    if (descriptor == NULL) {
      std::cout << "Failed to initialize plugin " << pluginPath << std::endl;
      return NULL;
    }
    return descriptor;
  }
  */
  return descriptor;
}

}
