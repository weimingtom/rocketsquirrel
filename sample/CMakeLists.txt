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
set(SFML_LIBS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/lib/win32)
set(SFML_LIBS
	debug ${SFML_LIBS_FOLDER}/sfml-main-d
	optimized ${SFML_LIBS_FOLDER}/sfml-main
	debug ${SFML_LIBS_FOLDER}/sfml-window-d
	optimized ${SFML_LIBS_FOLDER}/sfml-window
)


target_link_libraries(
	Sample
	RocketSquirrel
	optimized ${SQUIRREL_LIBS_DIR}/squirrel
	debug ${SQUIRREL_LIBS_DIR}/squirrel_d
	${SFML_LIBS}
)