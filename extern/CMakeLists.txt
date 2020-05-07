# Portaudio
add_subdirectory(portaudio EXCLUDE_FROM_ALL)
# TinySoundFont
set(TSF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  CACHE PATH "TinySoundFont include directory")

set(LADSPA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/ladspa
  CACHE PATH "ladspa include directory")

# also install it
install(FILES ${LADSPA_INCLUDE_DIR}/ladspa.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal)
install(FILES ${TSF_INCLUDE_DIR}/tsf.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal)

# for convenience setup a target
add_library(ladspa INTERFACE)
add_library(tsf INTERFACE)

target_include_directories(ladspa INTERFACE
  $<BUILD_INTERFACE:${LADSPA_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_include_directories(tsf INTERFACE
  $<BUILD_INTERFACE:${TSF_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# need to export target as well
install(TARGETS ladspa
  EXPORT ladspaTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(TARGETS tsf 
  EXPORT tsfTargets 
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
