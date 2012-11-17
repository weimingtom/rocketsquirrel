cmake_minimum_required (VERSION 2.6)
project (Sample)


set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)

include_directories(
	../include
	${SQUIRREL_INCLUDE_DIR}
)

add_executable(Sample sample.cpp)

set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)


target_link_libraries(
	Sample
	RocketSquirrel
	optimized ${SQUIRREL_LIBS_DIR}/squirrel.lib
	debug ${SQUIRREL_LIBS_DIR}/squirrel_d.lib
)

message("Be aware that squirrel 3.0 on VisualStudio debug output is \nthe same as the release, so rename the debug version to squirrel_d.lib")

