# Versioning
cmake_minimum_required(VERSION 3.10...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Variables so we don't repeat ourselves
set(LOCAL_PROJECT_VERSION     "1.0.0")
set(LOCAL_PROJECT_VENDOR      "Calvin University")
set(LOCAL_PROJECT_NAMESPACE   "tsal")
set(LOCAL_PROJECT_NAME        "tsal")
set(LOCAL_PROJECT_OUTPUT_NAME "tsal")
set(LOCAL_PROJECT_DESCRIPTION "Thread safe Autio Library")

set(CMAKE_INSTALL_PREFIX /usr/local/)

# Project details
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES C CXX)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

option(INSTALL_HEADERS "Install library headers" ON)
option(BUILD_TESTS "Build unit tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CheckIncludeFiles)
check_include_files(stddef.h HAVE_STDDEF_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(sys/time.h HAVE_SYSTIME_H)
check_include_files(unistd.h HAVE_UNISTD_H)

include(CheckFunctionExists)
check_function_exists(fseeko HAVE_FSEEKO)
check_function_exists(error_at_line HAVE_ERROR_AT_LINE)
check_function_exists(malloc HAVE_MALLOC)
check_function_exists(mbrtowc HAVE_MBRTOWC)
check_function_exists(mktime HAVE_MKTIME)
check_function_exists(realloc HAVE_REALLOC)
check_function_exists(strtod HAVE_STRTOD)
check_function_exists(atexit HAVE_ATEXIT)
check_function_exists(btowc HAVE_BTOWC)
check_function_exists(clock_gettime HAVE_CLOCK_GETTIME)
check_function_exists(getdelim HAVE_GETDELIM)
check_function_exists(isascii HAVE_ISASCII)
check_function_exists(iswprint HAVE_ISWPRINT)
check_function_exists(localeconv HAVE_LOCALECONV)
check_function_exists(localtime_r HAVE_LOCALTIME_R)
check_function_exists(mblen HAVE_MBLEN)
check_function_exists(mbrlen HAVE_MBRLEN)
check_function_exists(pow HAVE_POW)
check_function_exists(putenv HAVE_PUTENV)
check_function_exists(realpath HAVE_REALPATH)
check_function_exists(rpmatch HAVE_RPMATCH)
check_function_exists(select HAVE_SELECT)
check_function_exists(setenv HAVE_SETENV)
check_function_exists(setlocale HAVE_SETLOCALE)
check_function_exists(stime HAVE_STIME)
check_function_exists(strtol HAVE_STRTOL)
check_function_exists(strtoul HAVE_STROUL)
check_function_exists(strtoull HAVE_STROULL)
check_function_exists(tzset HAVE_TZSET)
check_function_exists(wcwidth HAVE_WCWIDTH)
check_function_exists(obstack HAVE_OBSTACK)

include(CheckTypeSize)
# # Check for integer types
check_type_size("short" SIZE_OF_SHORT)
check_type_size("int" SIZE_OF_INT)
check_type_size("long" SIZE_OF_LONG)
check_type_size("long long" SIZE_OF_LONG_LONG)

check_type_size("unsigned short" SIZE_OF_UNSIGNED_SHORT)
check_type_size("unsigned" SIZE_OF_UNSIGNED)
check_type_size("unsigned long" SIZE_OF_UNSIGNED_LONG)
check_type_size("unsigned long long" SIZE_OF_UNSIGNED_LONG_LONG)

check_type_size("__int64" __INT64)
check_type_size("unsigned __int64" UNSIGNED___INT64)

check_type_size(int16_t INT16_T)
check_type_size(int32_t INT32_T)
check_type_size(int64_t INT64_T)
check_type_size(intmax_t INTMAX_T)
check_type_size(uint8_t UINT8_T)
check_type_size(uint16_t UINT16_T)
check_type_size(uint32_t UINT32_T)
check_type_size(uint64_t UINT64_T)
check_type_size(uintmax_t UINTMAX_T)

check_type_size(size_t SIZE_T)
if(NOT HAVE_SIZE_T)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(size_t "uint64_t")
  else("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(size_t   "uint32_t")
  endif("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
endif(NOT HAVE_SIZE_T)

check_type_size(ssize_t SSIZE_T)
if(NOT HAVE_SSIZE_T)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(ssize_t "int64_t")
  else("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(ssize_t "long")
  endif("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
endif(NOT HAVE_SSIZE_T)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

    if(CMAKE_CXX_STANDARD EQUAL "98" )
      message(FATAL_ERROR "CMAKE_CXX_STANDARD:STRING=98 is not supported.")
    endif()

    if(NOT CMAKE_CXX_STANDARD)
      set(CMAKE_CXX_STANDARD 20) # Supported values are ``11``, ``14``, and ``17``.
    endif()
    if(NOT CMAKE_CXX_STANDARD_REQUIRED)
      set(CMAKE_CXX_STANDARD_REQUIRED ON)
    endif()
    if(NOT CMAKE_CXX_EXTENSIONS)
      set(CMAKE_CXX_EXTENSIONS OFF)
    endif()

    # Enable runtime search path support for dynamic libraries on OSX
    if(APPLE)
      set(CMAKE_MACOSX_RPATH 1)
    endif()

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(GNUInstallDirs)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
      set(DOXYGEN_GENERATE_HTML YES)
      set(DOXYGEN_EXCLUDE_PATTERNS
        */.git/*
        */.svn/*
        */.hg/*
        */CMakeFiles/*
        */_CPack_Packages/*
        DartConfiguration.tcl
        CMakeLists.txt
        CMakeCache.txt
        */extern/*
      )
      message(STATUS "Working on Doxygen")
      doxygen_add_docs(
        doxygen
        ${PROJECT_SOURCE_DIR}
        COMMENT "Generate man pages"
      )
      message(STATUS "Generated")
    else()
    message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# Git sumodule auto build
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/midifile")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/TinySoundFont")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/portaudio")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# System Dependencies
# find_package(Portaudio REQUIRED)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(OpenMP REQUIRED)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

add_subdirectory(extern)

# The compiled library code is here
add_subdirectory(src)

# The example code is here
add_subdirectory(examples)

# Testing only available if this is the main app
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Mark Wissink")
set(CPACK_PACKAGE_VERSION ${LOCAL_PROJECT_VERSION})
include(CPack)
