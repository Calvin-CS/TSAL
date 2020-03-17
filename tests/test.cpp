#include "LadspaManager.hpp"
#include "tsal.hpp"
#include <omp.h>
#include <ladspa.h>

using namespace tsal;

int main() {
  Mixer mixer;
  Synth synth;

  Delay delay;
  LadspaEffect effect;
  effect.loadPlugin("/home/mark/Downloads/ladspa_sdk_1.15/plugins/amp.so");
  mixer.add(effect);

  // LadspaManager manager;
  // const LADSPA_Descriptor * descriptor = manager.loadPlugin("/home/mark/Downloads/ladspa_sdk_1.15/plugins/amp.so");
  // LADSPA_Data * inputBuffer = (LADSPA_Data *) calloc(2048, sizeof(LADSPA_Data));
  // LADSPA_Data * outputBuffer = (LADSPA_Data *) calloc(2048, sizeof(LADSPA_Data));
  // LADSPA_Handle plugin = descriptor->instantiate(descriptor, 100);
  // for (unsigned i = 0; i < descriptor->PortCount; i++) {
  //   auto portDescriptor = descriptor->PortDescriptors[i];
  //   if (LADSPA_IS_PORT_CONTROL(portDescriptor)) {
  //     std::cout << "Port: " << descriptor->PortNames[i] << std::endl;
  //   }
  //   if (LADSPA_IS_PORT_AUDIO(portDescriptor)) {
  //     if (LADSPA_IS_PORT_INPUT(portDescriptor)) {
  //       std::cout << "Port Input: " << descriptor->PortNames[i] << std::endl;
  //       descriptor->connect_port(plugin, i, inputBuffer);
  //     } 
  //     if (LADSPA_IS_PORT_OUTPUT(portDescriptor)) {
  //       std::cout << "Port Output: " << descriptor->PortNames[i] << std::endl;
  //       descriptor->connect_port(plugin, i, outputBuffer);
  //     } 
  //   }
  // }
  // // descriptor->activate(plugin);
  // if (descriptor->activate == NULL) {
  //   std::cout << "This doesn't have an activate function" << std::endl;
  // } else {
  //   descriptor->activate(plugin);
  // }

  

  
  mixer.add(synth);
  // mixer.add(delay);
  mixer.add(effect);
  synth.play(tsal::C4);
  tsal::Util::thread_sleep(2000);
  synth.stop();
  tsal::Util::thread_sleep(3000);
  exit (0);
}
