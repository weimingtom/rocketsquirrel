cmake_minimum_required (VERSION 2.6)
project (RocketSquirrel)


#check for squirrel variables
if(NOT DEFINED SQUIRREL_LIBS_DIR )
	
	message( SEND_ERROR "SQUIRREL_LIBS_DIR is missing" )

endif()

if(NOT DEFINED SQUIRREL_INCLUDE_DIR )
	
	message( SEND_ERROR "SQUIRREL_INCLUDE_DIR is missing" )

endif()

if(NOT DEFINED SQRAT_INCLUDE_DIR )
	
	message( SEND_ERROR "SQRT_INCLUDE_DIR is missing" )

endif()







add_subdirectory (sample)

set(HDRS
	include/RocketSquirrel.h
)
 
set(SRCS
	source/RocketSquirrel.cpp
)

set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)

include_directories(
	${VIRUS_INCLUDES}
	include
	${SQUIRREL_INCLUDE_DIR}
	${SQRAT_INCLUDE_DIR}
)

add_library(RocketSquirrel STATIC ${HDRS} ${SRCS})

