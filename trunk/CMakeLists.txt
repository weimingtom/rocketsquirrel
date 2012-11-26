cmake_minimum_required (VERSION 2.6)
project (RocketSquirrel)


#check for squirrel variables
if(NOT DEFINED SQUIRREL_LIBS_DIR )
	
	message( SEND_ERROR "SQUIRREL_LIBS_DIR is missing" )

endif()

if(NOT DEFINED SQUIRREL_INCLUDE_DIR )
	
	message( SEND_ERROR "SQUIRREL_INCLUDE_DIR is missing" )

endif()

if(NOT DEFINED SQBIND_DIR )
	
	message( SEND_ERROR "SQBIND_DIR is missing" )

endif()

if(NOT DEFINED LIBROCKET_DIR )
	
	message( SEND_ERROR "LIBROCKET_DIR is missing" )

endif()


if (DEFINED WIN32)
	set(SQBIND_LIB_DEBUG ${SQBIND_DIR}/lib/Debug/sqbind_d.lib)
	set(SQBIND_LIB_OPTIMIZED ${SQBIND_DIR}/lib/Release/sqbind.lib)
elseif (DEFINED UNIX)
	
	set(SQBIND_LIB_DEBUG ${SQBIND_DIR}/libsqbind_d.a)
	set(SQBIND_LIB_OPTIMIZED ${SQBIND_DIR}/libsqbind.a)
endif()


set(ROCKETSQUIRREL_VERSION_MAJOR 0)
set(ROCKETSQUIRREL_VERSION_MINOR 1)
set(ROCKETSQUIRREL_SCRIPTS ${PROJECT_SOURCE_DIR}/scripts)

set(ROCKETSQUIRREL_CONFIG_DIR ${PROJECT_BINARY_DIR}/Config)

configure_file(
	"${PROJECT_SOURCE_DIR}/Config.h.in"
	"${ROCKETSQUIRREL_CONFIG_DIR}/Config.h"
)



if(DEFINED BUILD_SAMPLE )
	add_subdirectory (sample)
	set(BUILDING_SAMPLE ${BUILD_SAMPLE})
endif()

if(DEFINED BUILD_TESTS )
	add_subdirectory (tests)
	set(BUILD_TESTS ${BUILD_TESTS})
endif()



set(HDRS
	include/RocketSquirrel.h
)
 
set(SRCS
	source/RocketSquirrel.cpp
	
	source/BindingUtil.h
	source/BindingUtil.cpp
	source/NamespaceHelper.h
	source/NamespaceHelper.cpp
	
	#Core
	source/Core/Interfaces.h
	source/Core/Interfaces.cpp
	source/Core/DictionaryInterface.h
	source/Core/DictionaryInterface.cpp
	source/Core/VectorInterface.h
	source/Core/VectorInterface.cpp
	source/Core/VariantInterface.h
	source/Core/VariantInterface.cpp
	
	source/Core/ContextInstancer.h
	source/Core/ContextInstancer.cpp
	source/Core/ContextInterface.h
	source/Core/ContextInterface.cpp
	source/Core/ElementInterface.h
	source/Core/ElementInterface.cpp
	
	source/Core/ElementWrapper.h
	source/Core/ElementWrapper.cpp
	
	source/Core/ElementWrapper.h
	source/Core/ElementWrapper.cpp
	source/Core/ElementWrapperDerived.h
	source/Core/ElementWrapperDerived.cpp
	
	source/Core/EventInterface.h
	source/Core/EventInterface.cpp
	
	source/Debug.h
)

set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)

include_directories(
	${VIRUS_INCLUDES}
	include
	${SQUIRREL_INCLUDE_DIR}
	${LIBROCKET_DIR}/Include
	${SQBIND_DIR}/include
	${PROJECT_BINARY_DIR}
	${ROCKETSQUIRREL_CONFIG_DIR}
)

ADD_DEFINITIONS(-std=c++0x)
ADD_DEFINITIONS(-DSQBIND_STATIC)
ADD_DEFINITIONS(-DROCKETSQUIRREL_DEV)

add_library(RocketSquirrel STATIC ${HDRS} ${SRCS})
