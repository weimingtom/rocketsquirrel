#include <iostream>
#include <string>
#include "RocketSquirrel.h"

#include "Shell.h"
#include "Input.h"
#include "ShellRenderInterfaceOpenGL.h"
#include "ShellSystemInterface.h"

#include "Rocket/Core.h"
#include "Rocket/Debugger.h"
#include "../source/Debug.h"

#include <sqbind/SquirrelBind.h>

void DevelopingTests();
void GameLoop();
void ExecuteScript(const char* script);


int main()
{
	// Generic OS initialisation
	if (!Shell::Initialise("./") || !Shell::OpenWindow("RocketSquirrel Tests", true))
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

	Rocket::Core::RegisterPlugin(new Rocket::Core::Squirrel::Module());

	Rocket::Core::Initialise();

	DevelopingTests();


	// Create the main Rocket context and set it on the shell's input layer.
	Rocket::Core::Context* context = Rocket::Core::GetContext("ScriptsContext");
	if (context == NULL)
	{
		Rocket::Core::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	//Rocket::Debugger::Initialise(context);

	Input::SetContext(context);

	Shell::LoadFonts("./assets/");


	//Execute the script that will create the testing GUI
	ExecuteScript("LoadDocument.nut");

	Shell::EventLoop(GameLoop);

	Rocket::Core::Squirrel::CollectGarbage();

	Rocket::Core::Shutdown();

	Shell::CloseWindow();
	Shell::Shutdown();

	return 0;
}