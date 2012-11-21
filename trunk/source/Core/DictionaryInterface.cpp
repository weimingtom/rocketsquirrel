#include "DictionaryInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"


namespace Rocket {
namespace Core {
namespace Squirrel {







DictionaryInterface::DictionaryInterface()
{	
}

std::size_t DictionaryInterface::Size()
{
	return dict.Size();
}

void DictionaryInterface::SetItem(const char* key, const VariantInterface& value)
{
	dict.Set(key, value);
}

void DictionaryInterface::DelItem(const char* key)
{
	if (dict.Remove(key))
	{
		return;
	}
}

SQInteger DictionaryInterface::__GetItem(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	SQInteger count = sq_gettop(vm);
	ROCKETSQUIRREL_ASSERT(count >= 2);

	//Here we assume that the obj has been allocated already TODO??
	DictionaryInterface* instance = (DictionaryInterface*)squirrelGetInstance(vm);

	const SQChar* key = sqb::Get(sqb::TypeWrapper<const SQChar*>(), vm, 2);
	ROCKETSQUIRREL_ASSERT(key);

	VariantInterface* vari = instance->GetItem(key);

	if (!vari)
	{
		sh.ThrowNull();
		return 0;
	}

	return sqb::Push(vm, (*vari));
}

VariantInterface* DictionaryInterface::GetItem(const char* key)
{
	VariantInterface* variant = (VariantInterface*)dict.Get(key);
	if (!variant)
	{
		return 0x0;
	}
	return variant;
}

bool DictionaryInterface::Contains(const char* key)
{
	return dict.Get(key) != NULL;
}











}
}
}