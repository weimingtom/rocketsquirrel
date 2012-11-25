#include <Rocket/Core.h>
#include <RocketSquirrel.h>
#include "Config.h"
#include "../source/BindingUtil.h"
#include "../source/Debug.h"
#include "ShellRenderInterfaceOpenGL.h"
#include "Shell.h"


static HSQUIRRELVM vm = 0;

void ExecuteScript(const char* script)
{
	using Rocket::Core::String;
	static String scriptsDir(String(ROCKETSQUIRREL_SCRIPTS) + "/");

	SQRESULT sqr;

	sqr = Rocket::Core::Squirrel::CompileNutFile(vm, String(scriptsDir + script).CString());

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));
  
	sq_pushroottable(vm);

	sqr = sq_call(vm, 1, false, true);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_poptop(vm);
}

void DevelopingTests()
{
	using Rocket::Core::String;
	using Rocket::Core::StringList;

	vm = Rocket::Core::Squirrel::Module::instance().getSquirrelVM();

	StringList tests;
	tests.push_back("Interfaces.nut");
	tests.push_back("Dictionary.nut");
	tests.push_back("Variant.nut");
	tests.push_back("StringList.nut");
	tests.push_back("Context.nut");
	tests.push_back("Element.nut");


	for (unsigned int i = 0; i < tests.size(); i++)
	{
		ExecuteScript(tests[i].CString());
	}
}

void GameLoop()
{
	glClear(GL_COLOR_BUFFER_BIT);

	ExecuteScript("GameLoop.nut");

	Shell::FlipBuffers();
}