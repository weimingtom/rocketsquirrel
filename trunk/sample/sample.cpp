#include <iostream>
#include <string>
#include "RocketSquirrel.h"

#include "Shell.h"
#include "Input.h"
#include "ShellRenderInterfaceOpenGL.h"
#include "ShellSystemInterface.h"

#include "Rocket/Core.h"
#include "Rocket/Debugger.h"

#include "SquirrelGame.h"


SquirrelGame game;

void GameLoop()
{
	game.Tick();
}


int main()
{
	// Generic OS initialisation
	if (!Shell::Initialise("./") || !Shell::OpenWindow("RocketSquirrel Sample", true))
	{
		Shell::Shutdown();
		return -1;
	}

	// Rocket initialisation.
	ShellRenderInterfaceOpenGL opengl_renderer;
	Rocket::Core::SetRenderInterface(&opengl_renderer);

	// Initialise our system interface
	ShellSystemInterface system_interface;
	Rocket::Core::SetSystemInterface(&system_interface);



	//RocketSquirrel Sample Code
	///////////////////////////////////////////
	
	
	//Register the RocketSquirrel module (plugin)
	Rocket::Core::RegisterPlugin(new Rocket::Core::Squirrel::Module());

	///////////////////////////////////////////
	Rocket::Core::Initialise();

	game.initialize();

	//Main Loop
	Shell::EventLoop(GameLoop);

	game.destroy();

	Rocket::Core::Squirrel::CollectGarbage();

	// Shutdown Rocket.
	Rocket::Core::Shutdown();

	Shell::CloseWindow();
	Shell::Shutdown();

	return 0;
}