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

#include "EventInterface.h"
#include <Rocket/Core/Factory.h>
#include "EventListenerInstancer.h"
#include "EventWrapper.h"
#include "../NamespaceHelper.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






EventInterface::EventInterface()
{
}

//Binding function
void EventInterface::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	EventWrapper::Bind(vm);

	sq_poptop(vm);
	return;

}

void EventInterface::Register(HSQUIRRELVM vm)
{
}

void EventInterface::InitialiseRocketInterface()
{

	Rocket::Core::Factory::RegisterEventListenerInstancer(new EventListenerInstancer());

}







}
}
}