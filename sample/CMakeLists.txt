cmake_minimum_required (VERSION 2.6)
project (Sample)

INCLUDE(../CMake/subproject.cmake)

set(sources sample.cpp)

ROCKETSQUIRREL_EXECUTABLE(Sample)
