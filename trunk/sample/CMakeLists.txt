cmake_minimum_required (VERSION 2.6)
project (Sample)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)

#SFML
set(SFML_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/lib/win32)

set(SFML_BIN_DEBUG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/debug)
set(SFML_BIN_OPTIMIZED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/optimized)

set(SFML_BIN_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/external)


include_directories(
	../include
	${SQUIRREL_INCLUDE_DIR}
	${SQRAT_INCLUDE_DIR}
	./dependencies/SFML/include
)

link_directories(
	${SQUIRREL_LIBS_DIR}
	${SFML_LIBS_DIR}
)

add_executable(Sample sample.cpp)

set_target_properties(Sample PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(
	Sample
	RocketSquirrel
	optimized squirrel
	debug squirrel_d
	debug sfml-main-d
	optimized sfml-main
	debug sfml-window-d
	optimized sfml-window
)

if (MSVC_IDE)
    # hack to get around the "Debug" and "Release" directories cmake tries to add on Windows
    set_target_properties (${NAME} PROPERTIES PREFIX "../")
endif()