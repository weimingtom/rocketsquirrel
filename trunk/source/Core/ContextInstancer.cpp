#include "ContextInstancer.h"
#include "ContextInterface.h"
#include <Rocket/Core/Log.h>
#include "../Debug.h"



namespace Rocket {
namespace Core {
namespace Squirrel {



ContextInstancer* ContextInstancer::s_pInstance = 0x0;


ContextInstancer::ContextInstancer()
{
	s_pInstance = this;
}

ContextInstancer::~ContextInstancer()
{
}

Rocket::Core::Context* ContextInstancer::InstanceContext(const Rocket::Core::String& name)
{
	Rocket::Core::Context* context = 0x0;

	ContextMap::iterator it = mContexts.find(name.CString());

	if (it == mContexts.end())
	{
		context = new Context(name);
		mContexts[name.CString()] = context;
	}

	return context;
}

void ContextInstancer::ReleaseContext(Context* ROCKET_UNUSED(context))
{
	//TODO ??
}

void ContextInstancer::Release()
{
	s_pInstance = 0x0;
	delete this;
}

ContextInstancer& ContextInstancer::instance()
{
	ROCKETSQUIRREL_ASSERT(s_pInstance != 0x0);
	return *s_pInstance;
}








}
}
}