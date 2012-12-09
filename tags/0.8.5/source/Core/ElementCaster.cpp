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

#include "ElementCaster.h"
#include "../NamespaceHelper.h"
#include "../Debug.h"


namespace Rocket {
namespace Core {
namespace Squirrel {








void ElementCaster::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	sq_pushstring(vm, _SC("ElementAs"), -1);
	sq_newtable(vm);
	SQRESULT sqr = sq_newslot(vm, -3, SQTrue);
	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));


	sq_poptop(vm);
}

SQInteger ElementCaster::ThrowErrorUnknown(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	return sh.ThrowError("ElementAs: Unknown error while casting an element");
}

SQInteger ElementCaster::ThrowErrorNotElement(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	return sh.ThrowError("ElementAs: Cannot cast non-element instances");
}

SQInteger ElementCaster::ThrowErrorCastFailed(HSQUIRRELVM vm, const char* targetClass)
{
	sqb::StackHandler sh(vm);

	return sh.ThrowError("ElementAs: Failed to cast as '%s'!", targetClass);
}

void ElementCaster::SwitchTo(HSQUIRRELVM vm)
{
	sq_pushstring(vm, _SC("ElementAs"), -1);
	SQRESULT sqr = sq_get(vm, -2);
	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));
}






}
}
}