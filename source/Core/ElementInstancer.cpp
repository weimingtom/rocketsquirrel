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

#include "ElementInstancer.h"
#include "ElementDocument.h"
#include <sqbind/SquirrelBind.h>
#include <squirrel.h>
#include "RocketSquirrel/Core/Module.h"
#include "../NamespaceHelper.h"
#include "../Debug.h"
#include "ElementWrapperDerived.h"


namespace Rocket {
namespace Core {
namespace Squirrel {







ElementInstancer::ElementInstancer()
{
}

ElementInstancer::~ElementInstancer()
{
}

Element* ElementInstancer::InstanceElement(Element* parent, const Rocket::Core::String& tag, const Rocket::Core::XMLAttributes& attributes)
{
	ElementDocument* doc = new ElementDocument(tag);

	HSQUIRRELVM vm = Module::instance().getScriptInterface().getSquirrelVM();

	sq_pushroottable(vm);

	NamespaceHelper::switchTo(vm, "Rocket");

	SQRESULT sqr;

	sq_pushstring(vm, _SC("__docTables"), -1);
	sqr = sq_get(vm, -2);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_pushuserpointer(vm, (SQUserPointer)doc);
	sq_newtable(vm);
	sqr = sq_newslot(vm, -3, false);
	
	sq_pop(vm, 2);




	sq_pushroottable(vm);

	NamespaceHelper::switchTo(vm, "Rocket");

	sq_pushstring(vm, _SC("__docTables"), -1);
	sqr = sq_get(vm, -2);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_pushuserpointer(vm, (SQUserPointer)doc);
	sqr = sq_get(vm, -2);
	
	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	ElementDocumentWrapper wrapper;
	wrapper.setElement(doc);

	sq_pushstring(vm, _SC("document"), -1);
	sqb::Push(vm, wrapper);
	sqr = sq_newslot(vm, -3, true);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_pop(vm, 2);

	return doc;
}

void ElementInstancer::ReleaseElement(Element* element)
{
	delete element;
}

void ElementInstancer::Release()
{
	delete this;
}






}
}
}