cmake_minimum_required (VERSION 2.6)
project (Sample)

INCLUDE(../CMake/subproject.cmake)

set(sources sample.cpp SquirrelGame.h)

include_directories(${ROCKETSQUIRREL_CONFIG_DIR})

ROCKETSQUIRREL_EXECUTABLE(Sample)
