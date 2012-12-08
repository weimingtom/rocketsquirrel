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

#include "EventListener.h"
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include "RocketSquirrel/Core/Module.h"
#include "ElementDocument.h"
#include "ElementWrapper.h"
#include "ElementWrapperDerived.h"
#include "../BindingUtil.h"


namespace Rocket {
namespace Core {
namespace Squirrel {







EventListener::EventListener(const Rocket::Core::String& code, Rocket::Core::Element* context) :
	m_pElement(0x0)
{
	mScript.SetSourceCode(code);
}

EventListener::~EventListener()
{
	return;
}

void EventListener::ProcessEvent(Rocket::Core::Event& event)
{
	HSQUIRRELVM vm = Module::instance().getScriptInterface().getSquirrelVM();

	if (!mScript.IsCompiled())
	{
		mScript.Compile(vm, true);
	}

	GlobalUtility gutil(vm, m_pElement->GetOwnerDocument(), m_pElement, &event);

	SQInteger i = sq_gettop(vm);

	gutil.Set();

	mScript.Run(vm);

	gutil.Restore();

	sq_pop(vm, i);

	return;
}

void EventListener::OnAttach(Rocket::Core::Element* element)
{
	if (element)
	{
		m_pElement = element;
		mScript.SetSourceName(m_pElement->GetAddress());
	}
}

void EventListener::OnDetach(Rocket::Core::Element* element)
{
	m_pElement = 0x0;
}





}
}
}