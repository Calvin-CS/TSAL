# TinySoundFont
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
set(MIDIFILE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/midifile/include
  CACHE PATH "midifile include directory")

set(MIDIFILE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/extern/midifile/src
  CACHE PATH "midifile source directory")

if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
endif()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    option(STATIC_CRT "Use static CRT libraries" OFF)

    # Rewrite command line flags to use /MT if necessary
    if(STATIC_CRT)
        foreach(flag_var
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
            if(${flag_var} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
            endif(${flag_var} MATCHES "/MD")
        endforeach(flag_var)
    endif()
endif()

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

# Portaudio
add_subdirectory(portaudio EXCLUDE_FROM_ALL)
