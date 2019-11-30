# ${PROJECT_SOURCE_DIR}/include
# ${PROJECT_SOURCE_DIR}/include

# ${PROJECT_BINARY_DIR}/src/libtsal.la

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${TSAL_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${TSAL_SOURCE_DIR}/include/tsal.hpp")

set(SOURCES
  Channel.cpp
  Compressor.cpp
  Delay.cpp
  EffectChain.cpp
  Effect.cpp
  Envelope.cpp
  Instrument.cpp
  MidiParser.cpp
  Mixer.cpp
  Oscillator.cpp
  OutputDevice.cpp
  PolySynth.cpp
  ProgressOctave.cpp
  Sequencer.cpp
  SoundFont.cpp
  Synth.cpp
  ThreadSynth.cpp
  tsal.cpp
  Util.cpp
  )

add_subdirectory("${PROJECT_SOURCE_DIR}/extern/midifile" "extern/midifile")

# Make an automatic library - will be static or dynamic based on user setting
# add_library(tsal tsal.cpp ${HEADER_LIST})
add_library(tsal ${SOURCES} ${HEADER_LIST})
# add_library(tsal)
# target_sources(tsal PUBLIC ../include/tsal.hpp)

# We need this directory, and users of our library will need it too
target_include_directories(tsal
  PUBLIC ../include
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/midifile/include
  # PRIVATE ${PROJECT_SOURCE_DIR}/extern/midifile/src
  )

target_link_directories(tsal
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/midifile/include
  # PRIVATE ${PROJECT_SOURCE_DIR}/extern/midifile/src
  )

# This depends on (header only) boost
# target_link_libraries(tsal PRIVATE midifile Boost::boost)
target_link_libraries(tsal midifile portaudio OpenMP::OpenMP_CXX Threads::Threads soundfont)


# All users of this library will need at least C++11
target_compile_features(tsal PUBLIC cxx_std_14)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
