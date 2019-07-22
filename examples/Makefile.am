noinst_PROGRAMS = \
	hello_tsal \
	hello_tsal_threads \
	canon \
	rain \
	merge_sort \
	progress \
	producer_consumer \
	producer_consumer_percussion


AM_CXXFLAGS = -g -Wall -I$(top_srcdir)/include -I/usr/lib/gcc/x86_64-pc-linux-gnu/9.1.0/include -lrtaudio -fopenmp -pthread

hello_tsal_SOURCES = hello_tsal.cpp
hello_tsal_LDADD = $(top_builddir)/src/libtsal.la

hello_tsal_threads_SOURCES = hello_tsal_threads.cpp
hello_tsal_threads_LDADD = $(top_builddir)/src/libtsal.la

canon_SOURCES = canon.cpp
canon_LDADD = $(top_builddir)/src/libtsal.la

rain_SOURCES = rain.cpp
rain_LDADD = $(top_builddir)/src/libtsal.la

merge_sort_SOURCES = merge_sort.cpp
merge_sort_LDADD = $(top_builddir)/src/libtsal.la

progress_SOURCES = progress.cpp
progress_LDADD = $(top_builddir)/src/libtsal.la

producer_consumer_SOURCES = producer_consumer.cpp
producer_consumer_LDADD = $(top_builddir)/src/libtsal.la

producer_consumer_percussion_SOURCES = producer_consumer_percussion.cpp
producer_consumer_percussion_LDADD = $(top_builddir)/src/libtsal.la
