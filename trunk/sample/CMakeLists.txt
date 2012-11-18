cmake_minimum_required (VERSION 2.6)
project (Sample)

include_directories(
	../include
	${SQUIRREL_INCLUDE_DIR}
	${SQRAT_INCLUDE_DIR}
	./dependencies/SFML/include
)

add_executable(Sample sample.cpp)

set_target_properties(Sample PROPERTIES DEBUG_POSTFIX _d)

#SFML
set(SFML_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/lib/win32)

set(SFML_BIN_DEBUG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/debug)
set(SFML_BIN_OPTIMIZED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/optimized)

set(SFML_BIN_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SFML/win32/external)


link_directories(
	${SQUIRREL_LIBS_DIR}
	${SFML_LIBS_DIR}
)


ADD_CUSTOM_COMMAND(TARGET main POST_BUILD COMMAND main WORKING_DIRECTORY ../bin/${TARGET})
ADD_CUSTOM_COMMAND(TARGET main POST_BUILD COMMAND main COPY ${SFML_BIN_DEBUG_DIR} DESTINATION ../bin/${TARGET})
ADD_CUSTOM_COMMAND(TARGET main POST_BUILD COMMAND main COPY ${SFML_BIN_OPTIMIZED_DIR} DESTINATION ../bin/${TARGET})
ADD_CUSTOM_COMMAND(TARGET main POST_BUILD COMMAND main COPY ${SFML_BIN_EXTERNAL_DIR} DESTINATION ../bin/${TARGET})

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