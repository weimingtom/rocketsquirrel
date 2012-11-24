#include <Rocket/Core.h>
#include <RocketSquirrel.h>
#include "Config.h"
#include "../source/BindingUtil.h"
#include "../source/Debug.h"


void developingTests()
{
	using Rocket::Core::String;
	using Rocket::Core::StringList;

	HSQUIRRELVM vm = Rocket::Core::Squirrel::Module::instance().getSquirrelVM();

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