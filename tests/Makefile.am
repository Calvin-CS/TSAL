noinst_PROGRAMS = jubilate rain smart_sort test chord

AM_CXXFLAGS = -Wall -I$(top_srcdir)/include -I/usr/local/include/rtaudio -lrtaudio -fopenmp -pthread


jubilate_SOURCES = jubilate.cpp
jubilate_LDADD = $(top_builddir)/src/libtsal.la

rain_SOURCES = rain.cpp
rain_LDADD = $(top_builddir)/src/libtsal.la

smart_sort_SOURCES = smart_sort.cpp
smart_sort_LDADD = $(top_builddir)/src/libtsal.la

test_SOURCES = test.cpp
test_LDADD = $(top_builddir)/src/libtsal.la

chord_SOURCES = chord.cpp
chord_LDADD = $(top_builddir)/src/libtsal.la

TESTS = test
