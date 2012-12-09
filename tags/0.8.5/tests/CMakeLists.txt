cmake_minimum_required (VERSION 2.6)
project (Tests)

INCLUDE(../CMake/subproject.cmake)

set(sources tests.cpp main.cpp)

include_directories(${ROCKETSQUIRREL_CONFIG_DIR})

ROCKETSQUIRREL_EXECUTABLE(Tests)
