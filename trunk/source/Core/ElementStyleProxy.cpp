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

#include "ElementStyleProxy.h"
#include "ElementInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"

#include "ElementWrapperDerived.h"


namespace Rocket {
namespace Core {
namespace Squirrel {





ElementStyleProxy::ElementStyleProxy(const ElementStyleProxy& other) :
	m_pElement(0x0)
{
	operator=(other);
}

ElementStyleProxy::ElementStyleProxy(Rocket::Core::Element* pElement) :
	m_pElement(0x0)
{
	SetElement(pElement);
}

ElementStyleProxy::ElementStyleProxy() :
	m_pElement(0x0)
{
}

void ElementStyleProxy::SetElement(Rocket::Core::Element* pElement)
{
	m_pElement = pElement;
	m_pElement->AddReference();
}

ElementStyleProxy::~ElementStyleProxy()
{
	if (m_pElement)
	{
		m_pElement->RemoveReference();
	}
}

ElementStyleProxy& ElementStyleProxy::operator= (const ElementStyleProxy& other)
{
	ROCKETSQUIRREL_ASSERT(other.m_pElement != 0x0);
	
	SetElement(other.m_pElement);

	return *this;
}

SQInteger ElementStyleProxy::SetAttr(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	ROCKETSQUIRREL_ASSERT(sh.GetParamCount() >= 3);
	ROCKETSQUIRREL_ASSERT(sh.IsString(2));
	ROCKETSQUIRREL_ASSERT(sh.IsString(3));

	Rocket::Core::String key = Rocket::Core::String(sh.GetString(2)).Replace("_", "-");

	const char* value = sh.GetString(3);

	if (!m_pElement->SetProperty(key.CString(), value))
	{
		return sh.ThrowNull();
	}

	return 0;
}
	
SQInteger ElementStyleProxy::GetAttr(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	ROCKETSQUIRREL_ASSERT(sh.GetParamCount() >= 2);
	ROCKETSQUIRREL_ASSERT(sh.IsString(2));

	Rocket::Core::String key = Rocket::Core::String(sh.GetString(2)).Replace("_", "-");

	const Rocket::Core::Property* property = m_pElement->GetProperty(key.CString());
	if (!property)
	{
		return sh.ThrowNull();
	}

	mCache = property->ToString();

	return sqb::Push(vm, mCache.CString());
}

void ElementStyleProxy::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<ElementStyleProxy> cE(vm, -1, _SC("Style"));
	
	cE.Constructor(&NoConstructable);

	cE.NativeClassFunction(&ElementStyleProxy::SetAttr, _SC("_set"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xss")));
	cE.NativeClassFunction(&ElementStyleProxy::GetAttr, _SC("_get"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xs")));
}






}
}
}