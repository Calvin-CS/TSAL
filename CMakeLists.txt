# Versioning
cmake_minimum_required(VERSION 3.1...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Variables so we don't repeat ourselves
set(LOCAL_PROJECT_VERSION     "1.0.0")
set(LOCAL_PROJECT_VENDOR      "Calvin University")
set(LOCAL_PROJECT_NAMESPACE   "tsal")
set(LOCAL_PROJECT_NAME        "TSAL")
set(LOCAL_PROJECT_OUTPUT_NAME "tsal")
set(LOCAL_PROJECT_DESCRIPTION "Thread safe Autio Library")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Project details
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
    add_subdirectory(docs)
    else()
    message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
# include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
# if(${CMAKE_VERSION} VERSION_LESS 3.14)
#     include(cmake/add_FetchContent_MakeAvailable.cmake)
# endif()

# find_package(portaudio REQUIRED)
find_package(Portaudio REQUIRED)

# check if boost was found
# if(portaudio_FOUND)
#     message ("portaudio found")
# else()
#     message (FATAL_ERROR "Cannot find portaudio")
# endif()

# link against the boost libraries
# target_link_libraries( third_party_include
#     PRIVATE
#         PortAudio::Pa_GetVersion
# )

# Accumulator library
# This is header only, so could be replaced with git submodules or FetchContent
# find_package(Boost REQUIRED)
# Adds Boost::boost

# Formatting library
# FetchContent_Declare(
#   fmtlib
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG        5.3.0
# )

# FetchContent_MakeAvailable(fmtlib)
# Adds fmt::fmt

# The compiled library code is here
add_subdirectory(src)

# The example code is here
add_subdirectory(examples)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()


# Our build target is a static library. Other options are SHARED and MODULE.
# add_library(tsal STATIC
#         include/tsal.cpp
# )

# # Also make it accessible via namespace
# add_library(${LOCAL_PROJECT_NAMESPACE}::${LOCAL_PROJECT_NAME} ALIAS tsal)

# # place binaries and libraries according to GNU standards
# include(GNUInstallDirs)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)
# find_package(portaudio)

# # check if boost was found
# if(portaudio_FOUND)
#     message ("portaudio found")
# else()
#     message (FATAL_ERROR "Cannot find portaudio")
# endif()

# # link against the boost libraries
# target_link_libraries( third_party_include
#     PRIVATE
#         PortAudio::Pa_GetVersion
# )

# check_include_files(stddef.h HAVE_STDDEF_H)
# check_include_files(stdint.h HAVE_STDINT_H)
# check_include_files(stdlib.h HAVE_STDLIB_H)
# check_include_files(sys/time.h HAVE_SYSTIME_H)
# check_include_files(unistd.h HAVE_UNISTD_H)

# # If just pacakge
# # add_subdirectory("path to PortAudio location" "some binary directory" EXCLUDE_FROM_ALL)

# # Add sub directories
# add_subdirectory(src)
# add_subdirectory(tests)
# add_subdirectory(examples)
