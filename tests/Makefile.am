noinst_PROGRAMS = jubilate rain merge_sort test chord progress producer_consumer

AM_CXXFLAGS = -Wall -I$(top_srcdir)/include -lrtaudio -fopenmp -pthread

jubilate_SOURCES = jubilate.cpp
jubilate_LDADD = $(top_builddir)/src/libtsal.la

rain_SOURCES = rain.cpp
rain_LDADD = $(top_builddir)/src/libtsal.la

merge_sort_SOURCES = merge_sort.cpp
merge_sort_LDADD = $(top_builddir)/src/libtsal.la

test_SOURCES = test.cpp
test_LDADD = $(top_builddir)/src/libtsal.la

chord_SOURCES = chord.cpp
chord_LDADD = $(top_builddir)/src/libtsal.la

progress_SOURCES = progress.cpp
progress_LDADD = $(top_builddir)/src/libtsal.la

producer_consumer_SOURCES = producer_consumer.cpp
producer_consumer_LDADD = $(top_builddir)/src/libtsal.la

# Assign programs to run as tests with 'make check'
TESTS = test
