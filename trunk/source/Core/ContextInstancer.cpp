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

#include "ContextInstancer.h"
#include "ContextInterface.h"
#include <Rocket/Core/Log.h>
#include "../Debug.h"



namespace Rocket {
namespace Core {
namespace Squirrel {



ContextInstancer* ContextInstancer::s_pInstance = 0x0;


ContextInstancer::ContextInstancer()
{
	s_pInstance = this;
}

ContextInstancer::~ContextInstancer()
{
}

Rocket::Core::Context* ContextInstancer::InstanceContext(const Rocket::Core::String& name)
{
	Rocket::Core::Context* context = 0x0;

	ContextMap::iterator it = mContexts.find(name.CString());

	if (it == mContexts.end())
	{
		context = new Context(name);
		mContexts[name.CString()] = context;
	}

	return context;
}

void ContextInstancer::ReleaseContext(Context* ROCKET_UNUSED(context))
{
	//TODO ??
}

void ContextInstancer::Release()
{
	s_pInstance = 0x0;
	delete this;
}

ContextInstancer& ContextInstancer::instance()
{
	ROCKETSQUIRREL_ASSERT(s_pInstance != 0x0);
	return *s_pInstance;
}








}
}
}