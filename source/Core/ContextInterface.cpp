#include "ContextInterface.h"

#include <Rocket/Core/Context.h>
#include <Rocket/Core/Factory.h>
#include <Rocket/Core.h>
#include <Rocket/Core/Vector2.h>

#include "ContextInstancer.h"
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"
#include "Interfaces.h"



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

	Rocket::Core::Context* pRocketContext = Rocket::Core::CreateContext(name, dim);

	if (!pRocketContext)
	{
		return sh.ThrowError(_SC("Couldn't create the Context with name '%s'"), name.CString());
	}

	ContextInterface* pContext = NewInstance<ContextInterface>(v);

	pContext->m_pContext = pRocketContext;

	return 1;
}

void ContextInterface::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<ContextInterface> cCon(vm, -1, _SC("Context"));

	cCon.Constructor(&ContextInterface::constructor, sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xsx")));

	cCon.ClassFunction(&ContextInterface::Render, _SC("Render"));
	cCon.ClassFunction(&ContextInterface::Update, _SC("Update"));
	cCon.ClassFunction(&ContextInterface::GetName, _SC("GetName"));
	cCon.ClassFunction(&ContextInterface::GetDimensions, _SC("GetDimensions"));
	cCon.ClassFunction(&ContextInterface::SetDimensions, _SC("SetDimensions"));
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

bool ContextInterface::Render()
{
	return m_pContext->Render();
}

bool ContextInterface::Update()
{
	return m_pContext->Update();
}

const char* ContextInterface::GetName() const
{
	return m_pContext->GetName().CString();
}

const Rocket::Core::Vector2i& ContextInterface::GetDimensions() const
{
	return m_pContext->GetDimensions();
}

void ContextInterface::SetDimensions(const Rocket::Core::Vector2i& dim)
{
	return m_pContext->SetDimensions(dim);
}



}
}
}