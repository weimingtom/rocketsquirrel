/*
 * This source file is part of RocketSquirrel, libRocket Plugin / Module / Extension
 *
 * For the latest information, see http://code.google.com/p/rocketsquirrel/
 *
 * Copyright (c) 2012 Luis Jimenez
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

#include "VariantInterface.h"
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include "../BindingUtil.h"



namespace Rocket {
namespace Core {
namespace Squirrel {





VariantInterface::VariantInterface(const Rocket::Core::Variant& variant) :
	Rocket::Core::Variant(variant)
{
}


VariantInterface::VariantInterface()
{
	Set("");
}

VariantInterface::~VariantInterface()
{
}

SQInteger VariantInterface::constructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 2)
	{
		Rocket::Core::Squirrel::VariantInterface* pVari = NewInstance<Rocket::Core::Squirrel::VariantInterface>(v);

		switch (sq_gettype(v, 2))
		{
		case OT_STRING:
			{
				const SQChar* str;
				if (SQ_SUCCEEDED(sq_getstring(v, 2, &str)))
				{
					pVari->Set(str);
				}
			} 
			break;
		case OT_INTEGER:
			{
				SQInteger inte;
				if (SQ_SUCCEEDED(sq_getinteger(v, 2, &inte)))
				{
					pVari->Set((int)inte);
				}
			} 
			break;
		case OT_FLOAT:
			{
				float f;
				if (SQ_SUCCEEDED(sq_getfloat(v, 2, &f)))
				{
					pVari->Set(f);
				}
			} 
			break;
		case OT_INSTANCE:
			{
				TypeTagUtility ttu(v, 2);

				if (ttu.matches<Rocket::Core::Vector2f>())
				{
					pVari->Set(*((Rocket::Core::Vector2f*)GetInstance(v, 2)));
				}
			}
			break;
		default:
			{
			}
			break;
		}

		return 1;
	}	

	return sqb::ClassDefinition<Rocket::Core::Squirrel::VariantInterface>::DefaultConstructor(v);
}

const char* VariantInterface::toString()
{
	mCacheStr.Clear();
	mCacheStr = Get<Rocket::Core::String>();

	return mCacheStr.CString();
}

float VariantInterface::toFloat()
{
	return Get<float>();
}

int32_t VariantInterface::toInteger()
{
	return Get<int32_t>();
}

Rocket::Core::Vector2f VariantInterface::toVector2f()
{
	return Rocket::Core::Vector2f(Get<Rocket::Core::Vector2f>());
}

Rocket::Core::Vector2i VariantInterface::toVector2i()
{
	return Rocket::Core::Vector2i(Get<Rocket::Core::Vector2i>());
}

void VariantInterface::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<VariantInterface> cVar(vm, -1, _SC("Variant"));

	cVar.Constructor(&VariantInterface::constructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("x")));

	cVar.ClassFunction(&VariantInterface::toString, _SC("_tostring"));
	cVar.ClassFunction(&VariantInterface::toFloat, _SC("tofloat"));
	cVar.ClassFunction(&VariantInterface::toInteger, _SC("tointeger"));
	cVar.ClassFunction(&VariantInterface::toVector2f, _SC("toVector2f"));
	cVar.ClassFunction(&VariantInterface::toVector2i, _SC("toVector2i"));

}








}
}
}
