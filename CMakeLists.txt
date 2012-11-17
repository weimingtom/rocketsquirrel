cmake_minimum_required (VERSION 2.6)
project (RocketSquirrel)

set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)

include_directories(
	${VIRUS_INCLUDES}
	include
)

add_library(RocketSquirrel SHARED ${HDRS} ${SRCS})

