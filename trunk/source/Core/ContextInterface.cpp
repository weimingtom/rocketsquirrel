#include "ContextInterface.h"

#include <Rocket/Core/Context.h>
#include <Rocket/Core/Factory.h>
#include <Rocket/Core.h>
#include <Rocket/Core/Vector2.h>

#include "ContextInstancer.h"
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






ContextInterface::ContextInterface()
{
}

SQInteger ContextInterface::constructor(HSQUIRRELVM v)
{
	sqb::StackHandler sh(v);

	Rocket::Core::String name;
	Rocket::Core::Vector2i dim(800, 600);

	ContextInterface* pContext = NewInstance<ContextInterface>(v);

	SQInteger args = sh.GetParamCount();

	if (args >= 2)
	{
		if (sh.IsString(2))
		{
			name = sh.GetString(2);
		}

		if (args >= 3)
		{
			if (sh.IsInstance(3) && sh.IsInstanceOfType<Rocket::Core::Vector2i>(3))
			{
				dim = *sh.GetInstanceAsType<Rocket::Core::Vector2i>(3);
			}
		}
	}

	//App will close if cannot create the context
	pContext->m_pContext = Rocket::Core::CreateContext(name, dim);

	ROCKETSQUIRREL_ASSERT(pContext->m_pContext != 0x0);

	return 1;
}

void ContextInterface::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<ContextInterface> cCon(vm, -1, _SC("Context"));

	cCon.Constructor(&ContextInterface::constructor, sqb::FunctionOptions().ParamCheckCount(2).TypeMask(_SC("xsx")));

}

void ContextInterface::Register(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	Bind(vm);

	sq_poptop(vm);
}

void ContextInterface::InitialiseRocketInterface()
{
	ContextInstancer* instancer = new ContextInstancer();
	Rocket::Core::Factory::RegisterContextInstancer(instancer);
	instancer->RemoveReference();
}




}
}
}