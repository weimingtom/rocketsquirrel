cmake_minimum_required (VERSION 2.6)
project (Sample)

include_directories(
	../include
	${SQUIRREL_INCLUDE_DIR}
	${SQRAT_INCLUDE_DIR}
)

add_executable(Sample sample.cpp)

set_target_properties(Sample PROPERTIES DEBUG_POSTFIX _d)

#SFML Stuff

set(SFML_LIBS
	debug ${CMAKE_CURRENT_SOURCE_DIR}/
)


target_link_libraries(
	Sample
	RocketSquirrel
	optimized ${SQUIRREL_LIBS_DIR}/squirrel.lib
	debug ${SQUIRREL_LIBS_DIR}/squirrel_d.lib
)