#include "NamespaceHelper.h"



namespace Rocket {
namespace Core {
namespace Squirrel {




bool NamespaceHelper::switchTo(HSQUIRRELVM vm, const char* name)
{
	sq_pushroottable(vm);
	sq_pushstring(vm, _SC(name), -1);
	return SQ_SUCCEEDED(sq_get(vm, -2));
}

bool NamespaceHelper::create(HSQUIRRELVM vm, const char* name)
{
	sq_pushstring(vm, _SC(name), -1);
	sq_newtable(vm);
	return SQ_SUCCEEDED(sq_newslot(vm, -3, SQTrue));
}





}
}
}