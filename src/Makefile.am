AM_CXXFLAGS = -Wall -I$(top_srcdir)/include -lportaudio

lib_LTLIBRARIES = libtsal.la
libtsal_la_SOURCES = \
  Binasc.cpp \
  Channel.cpp \
  Compressor.cpp \
  Delay.cpp \
  Effect.cpp \
  EffectChain.cpp \
  Envelope.cpp \
	Instrument.cpp \
  MidiEvent.cpp \
  MidiEventList.cpp \
  MidiFile.cpp \
  MidiMessage.cpp \
  MidiParser.cpp \
  Sequencer.cpp \
  Mixer.cpp \
  Oscillator.cpp \
  OutputDevice.cpp \
	PolySynth.cpp \
	ProgressOctave.cpp \
	SoundFont.cpp \
  Synth.cpp \
	ThreadSynth.cpp \
  Util.cpp

includedir=${prefix}/include/tsal
include_HEADERS = \
  $(top_srcdir)/include/tsal.hpp \
  $(top_srcdir)/include/tsf.hpp \
  $(top_srcdir)/include/AudioBuffer.hpp \
  $(top_srcdir)/include/Binasc.h \
  $(top_srcdir)/include/Buffer.hpp \
  $(top_srcdir)/include/Channel.hpp \
  $(top_srcdir)/include/ChannelDevice.hpp \
  $(top_srcdir)/include/Compressor.hpp \
  $(top_srcdir)/include/Delay.hpp \
  $(top_srcdir)/include/Effect.hpp \
  $(top_srcdir)/include/EffectChain.hpp \
  $(top_srcdir)/include/Envelope.hpp \
  $(top_srcdir)/include/InputDevice.hpp \
  $(top_srcdir)/include/Instrument.hpp \
  $(top_srcdir)/include/MidiEvent.h \
  $(top_srcdir)/include/MidiEventList.h \
  $(top_srcdir)/include/MidiFile.h \
  $(top_srcdir)/include/MidiMessage.h \
  $(top_srcdir)/include/MidiNotes.hpp \
  $(top_srcdir)/include/MidiParser.hpp \
  $(top_srcdir)/include/Sequencer.hpp \
  $(top_srcdir)/include/Mixer.hpp \
  $(top_srcdir)/include/Oscillator.hpp \
  $(top_srcdir)/include/OutputDevice.hpp \
	$(top_srcdir)/include/PolySynth.hpp \
  $(top_srcdir)/include/ProgressOctave.hpp \
  $(top_srcdir)/include/RouteDevice.hpp \
  $(top_srcdir)/include/SoundFont.hpp \
	$(top_srcdir)/include/Synth.hpp \
	$(top_srcdir)/include/ThreadSynth.hpp \
  $(top_srcdir)/include/Timing.hpp \
  $(top_srcdir)/include/Util.hpp

