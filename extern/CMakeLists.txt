# Portaudio
add_subdirectory(portaudio EXCLUDE_FROM_ALL)
# TinySoundFont
set(LADSPA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/ladspa
  CACHE PATH "ladspa include directory")

# also install it
install(FILES ${LADSPA_INCLUDE_DIR}/ladspa.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal)

# for convenience setup a target
add_library(ladspa INTERFACE)

target_include_directories(ladspa INTERFACE
  $<BUILD_INTERFACE:${LADSPA_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# need to export target as well
install(TARGETS ladspa
  EXPORT ladspaTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
