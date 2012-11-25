#include <Rocket/Core.h>
#include <RocketSquirrel.h>
#include "Config.h"
#include "../source/BindingUtil.h"
#include "../source/Debug.h"
#include "ShellRenderInterfaceOpenGL.h"
#include "Shell.h"


static HSQUIRRELVM vm = 0;


void developingTests()
{
	using Rocket::Core::String;
	using Rocket::Core::StringList;

	vm = Rocket::Core::Squirrel::Module::instance().getSquirrelVM();

	String scriptsDir(ROCKETSQUIRREL_SCRIPTS);
	scriptsDir += "/";


	StringList tests;
	tests.push_back("Interfaces.nut");
	tests.push_back("Dictionary.nut");
	tests.push_back("Variant.nut");
	tests.push_back("StringList.nut");
	tests.push_back("Context.nut");


	for (unsigned int i = 0; i < tests.size(); i++)
	{
		SQRESULT sqr;

		sqr = Rocket::Core::Squirrel::CompileNutFile(vm, String(scriptsDir + tests[i]).CString());

		ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));
  
		sq_pushroottable(vm);

		sqr = sq_call(vm, 1, false, true);

		ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

		sq_poptop(vm);
	}



}

void GameLoop()
{
	using Rocket::Core::String;
	glClear(GL_COLOR_BUFFER_BIT);

	static String gameLoopScript(String(ROCKETSQUIRREL_SCRIPTS) + "/GameLoop.nut");

	SQRESULT sqr;

	sqr = Rocket::Core::Squirrel::CompileNutFile(vm, gameLoopScript.CString());

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));
  
	sq_pushroottable(vm);

	sqr = sq_call(vm, 1, false, true);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_poptop(vm);


	Shell::FlipBuffers();
}