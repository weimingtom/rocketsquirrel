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

void developingTests();

static Rocket::Core::Context* context = NULL;

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	context->Update();
	context->Render();

	Shell::FlipBuffers();
}


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

	developingTests();

	// Create the main Rocket context and set it on the shell's input layer.
	context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(1024, 768));
	if (context == NULL)
	{
		Rocket::Core::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	Rocket::Debugger::Initialise(context);
	Input::SetContext(context);

	Shell::LoadFonts("./assets/");

	//Main Loop
	Shell::EventLoop(GameLoop);

	// Shutdown Rocket.
	context->RemoveReference();
	Rocket::Core::Shutdown();

	Shell::CloseWindow();
	Shell::Shutdown();

	return 0;
}