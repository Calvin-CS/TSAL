noinst_PROGRAMS = rain

AM_CXXFLAGS = -Wall -I$(top_srcdir)/include -I/usr/local/include/rtaudio -lrtaudio -fopenmp -pthread

rain_SOURCES = rain.cpp
rain_LDADD = $(top_builddir)/src/libtsal.la

TESTS = test
