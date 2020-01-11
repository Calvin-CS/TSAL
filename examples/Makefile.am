noinst_PROGRAMS = \
	bubble_sort \
	hello_tsal \
	hello_tsal_threads \
	insertion_sort \
	quick_sort \
	selection_sort \
	progress	


AM_CXXFLAGS = -g -Wall -I$(top_srcdir)/include -I/usr/lib/gcc/x86_64-pc-linux-gnu/9.1.0/include -fopenmp -pthread

bubble_sort_SOURCES = bubble_sort.cpp
bubble_sort_LDADD = $(top_builddir)/src/libtsal.la

hello_tsal_SOURCES = hello_tsal.cpp
hello_tsal_LDADD = $(top_builddir)/src/libtsal.la

hello_tsal_threads_SOURCES = hello_tsal_threads.cpp
hello_tsal_threads_LDADD = $(top_builddir)/src/libtsal.la

# canon_SOURCES = canon.cpp
# canon_LDADD = $(top_builddir)/src/libtsal.la

insertion_sort_SOURCES = insertion_sort.cpp
insertion_sort_LDADD = $(top_builddir)/src/libtsal.la

quick_sort_SOURCES = quick_sort.cpp
quick_sort_LDADD = $(top_builddir)/src/libtsal.la

selection_sort_SOURCES = selection_sort.cpp
selection_sort_LDADD = $(top_builddir)/src/libtsal.la

# merge_sort_SOURCES = merge_sort.cpp
# merge_sort_LDADD = $(top_builddir)/src/libtsal.la

progress_SOURCES = progress.cpp
progress_LDADD = $(top_builddir)/src/libtsal.la

# producer_consumer_SOURCES = producer_consumer.cpp
# producer_consumer_LDADD = $(top_builddir)/src/libtsal.la
