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

#include "ElementInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"
#include "ElementWrapper.h"
#include "ElementWrapperDerived.h"
#include "VariantInterface.h"
#include "VectorInterface.h"
#include "ElementStyleProxy.h"
#include "ElementInstancer.h"
#include <Rocket/Core/Factory.h>


namespace Rocket {
namespace Core {
namespace Squirrel {






ElementInterface::ElementInterface()
{	
}

void ElementInterface::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");


	ElementStyleProxy::Bind(vm);


	//ElementList
	sqb::ClassDefinition<VectorInterface<ElementWrapperList>> cVec(vm, -1, _SC("ElementList"));

	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::Contains, _SC("Contains"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::SetItem, _SC("_set"));
	cVec.NativeClassFunction(&VectorInterface<ElementWrapperList>::GetItem, _SC("_get"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xi")));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::PushBack, _SC("append"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::PushBack, _SC("push"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::Size, _SC("len"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::DelItem, _SC("remove"));

	ElementWrapper::Bind(vm);
	ElementDocumentWrapper::Bind(vm);
	ElementTextWrapper::Bind(vm);

	//hmm can't access ElementTextDefault, ElementImage and ElementHandle


	/*
	.def("AddEventListener", AddEventListener)
	.def("AddEventListener", AddEventListenerDefault)
	.def("DispatchEvent", &ElementInterface::DispatchEvent)*/

	sq_poptop(vm);
}

void ElementInterface::InitialiseRocketInterface()
{
	Rocket::Core::Factory::RegisterElementInstancer("body", new ElementInstancer());
}












}
}
}