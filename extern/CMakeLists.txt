# TinySoundFont
find_path(TSF_INCLUDE_DIR tsf.h TinySoundFont)

if(NOT EXISTS ${TSF_INCLUDE_DIR})
    message("Unable to find TinySoundFont Library")

    execute_process(COMMAND git submodule update --init -- external/TinySoundFont
                    # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

set(TSF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  CACHE PATH "TinySoundFont include directory")

# also install it
install(FILES ${TSF_INCLUDE_DIR}/tsf.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal)

# for convenience setup a target
add_library(tsf INTERFACE)

target_include_directories(tsf INTERFACE
  $<BUILD_INTERFACE:${TSF_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# need to export target as well
install(TARGETS tsf
  EXPORT tsfTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

# Midifile: midifile had bad cmake support so just replicate it

## TODO: Add upstream change so that static is optional
## and better support for submoduling
# add_subdirectory(midifile)
find_path(MIDIFILE_INCLUDE_DIR MidiFile.h midifile/include)

if(NOT EXISTS ${MIDIFILE_INCLUDE_DIR})
    message("Unable to find TinySoundFont Library")

    execute_process(COMMAND git submodule update --init -- external/midifile
                    # WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

set(MIDIFILE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/midifile/include
  CACHE PATH "midifile include directory")

set(MIDIFILE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extern/midifile/src
  CACHE PATH "midifile source directory")

set(MIDIFILE_SOURCES
    ${MIDIFILE_SOURCE_DIR}/Options.cpp
    ${MIDIFILE_SOURCE_DIR}/Binasc.cpp
    ${MIDIFILE_SOURCE_DIR}/MidiEvent.cpp
    ${MIDIFILE_SOURCE_DIR}/MidiEventList.cpp
    ${MIDIFILE_SOURCE_DIR}/MidiFile.cpp
    ${MIDIFILE_SOURCE_DIR}/MidiMessage.cpp
)

set(MIDIFILE_PUBLIC_HEADERS
    ${MIDIFILE_INCLUDE_DIR}/Binasc.h
    ${MIDIFILE_INCLUDE_DIR}/MidiEvent.h
    ${MIDIFILE_INCLUDE_DIR}/MidiEventList.h
    ${MIDIFILE_INCLUDE_DIR}/MidiFile.h
    ${MIDIFILE_INCLUDE_DIR}/MidiMessage.h
    ${MIDIFILE_INCLUDE_DIR}/Options.h
)

install(FILES ${MIDIFILE_PUBLIC_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal)

# for convenience setup a target
add_library(midifile SHARED ${MIDIFILE_SOURCES})

target_include_directories(midifile PUBLIC
  $<BUILD_INTERFACE:${MIDIFILE_INCLUDE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# need to export target as well
install(TARGETS midifile
  EXPORT midifileTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
