noinst_PROGRAMS = \
	test \
	mixer


AM_CXXFLAGS = -g -Wall -I$(top_srcdir)/include -I/usr/lib/gcc/x86_64-pc-linux-gnu/9.1.0/include -lrtaudio -fopenmp -pthread

test_SOURCES = test.cpp
test_LDADD = $(top_builddir)/src/libtsal.la

mixer_SOURCES = mixer.cpp
mixer_LDADD = $(top_builddir)/src/libtsal.la

# Assign programs to run as tests with 'make check'
TESTS = test mixer
