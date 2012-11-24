find_package(OpenGL REQUIRED)

MACRO(ROCKETSQUIRREL_EXECUTABLE projectName)

	include_directories(
		../include
		${SQUIRREL_INCLUDE_DIR}
		../shell/include
		${LIBROCKET_DIR}/Include
		${SQBIND_DIR}/include
	)

	link_directories(
		${SQUIRREL_LIBS_DIR}
		${LIBROCKET_DIR}/bin
	)

	set(ShellSources 
		../shell/src/Shell.cpp
		../shell/src/Input.cpp
		../shell/src/ShellFileInterface.cpp
		../shell/src/ShellRenderInterfaceOpenGL.cpp
		../shell/src/ShellSystemInterface.cpp
	)

	if (DEFINED WIN32)
		set(ShellOSSources
			../shell/src/win32/InputWin32.cpp
			../shell/src/win32/ShellWin32.cpp
		)
	elseif (DEFINED UNIX)
		
		find_package(X11 REQUIRED)
		
		include_directories(${X11_INCLUDE_DIR})

		set(ShellOSSources
			../shell/src/x11/InputX11.cpp
			../shell/src/x11/ShellX11.cpp
		)
	endif()



	add_definitions( -DSQBIND_STATIC )

	add_executable(${projectName} ${sources} ${ShellSources} ${ShellOSSources})

	set_target_properties(${projectName} PROPERTIES DEBUG_POSTFIX _d)

	ADD_DEFINITIONS(-std=c++0x)
	ADD_DEFINITIONS(-DSQBIND_STATIC)

	target_link_libraries(
		${projectName}
		RocketSquirrel
		debug ${SQBIND_LIB_DEBUG}
		optimized ${SQBIND_LIB_OPTIMIZED}
		optimized squirrel
		debug squirrel_d
		optimized sqstdlib
		debug sqstdlib_d
		debug RocketControls_d
		optimized RocketControls
		debug RocketCore_d
		optimized RocketCore
		debug RocketDebugger_d
		optimized RocketDebugger
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
	)
ENDMACRO(ROCKETSQUIRREL_EXECUTABLE)