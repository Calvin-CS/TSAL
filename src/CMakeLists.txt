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
add_library(tsal ${SOURCES} ${HEADER_LIST})
# Also make it accessible via namespace
add_library(${LOCAL_PROJECT_NAMESPACE}::${LOCAL_PROJECT_NAME} ALIAS tsal)

# We need this directory, and users of our library will need it too
target_include_directories(tsal
  PUBLIC ../include
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/midifile/include
  PRIVATE ${PROJECT_SOURCE_DIR}/extern/midifile/src
  )

target_link_directories(tsal
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/TinySoundFont
  PUBLIC ${PROJECT_SOURCE_DIR}/extern/midifile/include
  PRIVATE ${PROJECT_SOURCE_DIR}/extern/midifile/src
  )

target_link_libraries(tsal
  portaudio
  OpenMP::OpenMP_CXX
  Threads::Threads
  midifile
  # PortAudio::Pa_GetVersion
  )

target_compile_options(tsal PRIVATE -Wall -Werror)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
