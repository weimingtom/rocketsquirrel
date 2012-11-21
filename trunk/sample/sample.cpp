#include <iostream>
#include <string>
#include "RocketSquirrel.h"

#include "Shell.h"
#include "Input.h"
#include "ShellRenderInterfaceOpenGL.h"
#include "ShellSystemInterface.h"

#include "Rocket/Core.h"
#include "Rocket/Debugger.h"

#include <sqbind/sqbBind.h>
#include <sqbind/sqbBindMacros.h>
#include <sqbind/sqbClassDefinition.h>


static Rocket::Core::Context* context = NULL;

SQBIND_DECLARE_CLASS(Rocket::Core::Box);
//SQBIND_DECLARE_CLASS(Rocket::Core::Vector2f);

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
	Rocket::Core::RegisterPlugin(new Rocket::Squirrel::Module());

	///////////////////////////////////////////
	Rocket::Core::Initialise();

	/*Warning all scripting should be done after Rocket Core initialization*/


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

	// Load and show the demo document.
	Rocket::Core::ElementDocument* document = context->LoadDocument("./assets/demo.rml");
	if (document != NULL)
	{
		document->Show();
		document->RemoveReference();
	}

	//Main Loop
	Shell::EventLoop(GameLoop);

	// Shutdown Rocket.
	context->RemoveReference();
	Rocket::Core::Shutdown();

	Shell::CloseWindow();
	Shell::Shutdown();

	return 0;
}