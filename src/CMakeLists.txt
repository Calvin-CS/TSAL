# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${TSAL_SOURCE_DIR}/include/*.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/tsal.hpp")

set(TSAL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/tsal)

SET(BUILD_SHARED_LIBS ON)

set(PUBLIC_HEADERS
  ${TSAL_INCLUDE_DIR}/AudioBuffer.hpp
  ${TSAL_INCLUDE_DIR}/Buffer.hpp
  ${TSAL_INCLUDE_DIR}/ChannelDevice.hpp
  ${TSAL_INCLUDE_DIR}/Channel.hpp
  ${TSAL_INCLUDE_DIR}/Compressor.hpp
  ${TSAL_INCLUDE_DIR}/Delay.hpp
  ${TSAL_INCLUDE_DIR}/EffectChain.hpp
  ${TSAL_INCLUDE_DIR}/Effect.hpp
  ${TSAL_INCLUDE_DIR}/Envelope.hpp
  ${TSAL_INCLUDE_DIR}/InputDevice.hpp
  ${TSAL_INCLUDE_DIR}/Instrument.hpp
  # ${TSAL_INCLUDE_DIR}/MidiNotes.hpp
  # ${TSAL_INCLUDE_DIR}/MidiParser.hpp
  ${TSAL_INCLUDE_DIR}/Mixer.hpp
  ${TSAL_INCLUDE_DIR}/Oscillator.hpp
  ${TSAL_INCLUDE_DIR}/OutputDevice.hpp
  ${TSAL_INCLUDE_DIR}/PolySynth.hpp
  ${TSAL_INCLUDE_DIR}/ProgressOctave.hpp
  ${TSAL_INCLUDE_DIR}/RouteDevice.hpp
  ${TSAL_INCLUDE_DIR}/Sequencer.hpp
  ${TSAL_INCLUDE_DIR}/Synth.hpp
  ${TSAL_INCLUDE_DIR}/ThreadSynth.hpp
  ${TSAL_INCLUDE_DIR}/Timing.hpp
  ${TSAL_INCLUDE_DIR}/tsal.hpp
  ${TSAL_INCLUDE_DIR}/Util.hpp
  )

set(SOURCES
  Channel.cpp
  Compressor.cpp
  Delay.cpp
  EffectChain.cpp
  Effect.cpp
  Envelope.cpp
  Instrument.cpp
  # MidiParser.cpp
  Mixer.cpp
  Oscillator.cpp
  OutputDevice.cpp
  PolySynth.cpp
  ProgressOctave.cpp
  Sequencer.cpp
  Synth.cpp
  ThreadSynth.cpp
  Util.cpp
  )

# Make an automatic library - will be static or dynamic based on user setting
add_library(tsal SHARED ${SOURCES} ${HEADER_LIST})
# Also make it accessible via namespace
add_library(${LOCAL_PROJECT_NAMESPACE}::${LOCAL_PROJECT_NAME} ALIAS tsal)

# We need this directory, and users of our library will need it too
target_include_directories(tsal
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  )

target_link_libraries(tsal
  PUBLIC
    portaudio
    OpenMP::OpenMP_CXX
    Threads::Threads
  )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    # target_compile_options(tsal PRIVATE -Wall -Werror -Wextra -Wunreachable-code -Wpedantic)
    # target_compile_options(tsal PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
    target_compile_options(tsal PRIVATE -Wall)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(tsal PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(tsal PRIVATE /W4 /w44265 /w44061 /w44062)
endif()

set_target_properties(tsal
  PROPERTIES
  OUTPUT_NAME "tsal"
  )

# IDEs should put the headers in a nice place
# source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})

# install(TARGETS tsal midifile tsf
install(TARGETS tsal
  EXPORT tsalTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )


# installation - build tree specific package config files

install(EXPORT tsalTargets
    FILE TsalTargets.cmake
    NAMESPACE ${LOCAL_PROJECT_NAMESPACE}::
    DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES ${PUBLIC_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tsal
    # FILES_MATCHING PATTERN "*.h*"
)

#####################
# ConfigVersion file
##
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/TsalConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/TsalConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/TsalConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

## Install all the helper files
install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/TsalConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/TsalConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)
