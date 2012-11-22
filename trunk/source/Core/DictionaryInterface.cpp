/*
 * This source file is part of RocketSquirrel, libRocket Plugin / Module / Extension
 *
 * For the latest information, see http://code.google.com/p/rocketsquirrel/
 *
 * Copyright (c) 2012 Kuko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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

void DictionaryInterface::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<DictionaryInterface> cDic(vm, -1, _SC("Dictionary"));

	cDic.ClassFunction(&DictionaryInterface::Size, _SC("len"));
	cDic.ClassFunction(&DictionaryInterface::SetItem, _SC("_set"));
	cDic.ClassFunction(&DictionaryInterface::DelItem, _SC("remove"));
	cDic.NativeFunction(&DictionaryInterface::__GetItem, _SC("_get"), sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xs")));
	cDic.ClassFunction(&DictionaryInterface::Contains, _SC("Contains"));
}












}
}
}