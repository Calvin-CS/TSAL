#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TSAL], [1.0.0])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile examples/Makefile])
# I may need this but not right now
# AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AM_PROG_AR

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([portaudio], [PortAudio::Pa_GetVersion])

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([stddef.h stdint.h stdlib.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_FUNC_OBSTACK
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_STRUCT_TIMEZONE
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FSEEKO
AC_FUNC_MALLOC
AC_FUNC_MBRTOWC
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit btowc clock_gettime getdelim isascii iswprint localeconv localtime_r mblen mbrlen pow putenv realpath rpmatch select setenv setlocale stime strtol strtoul strtoull tzset wcwidth])

AC_CONFIG_MACRO_DIR([m4])

AC_OUTPUT
