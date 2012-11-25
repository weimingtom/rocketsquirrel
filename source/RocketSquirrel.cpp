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

#include "RocketSquirrel.h"
#include <Rocket/Core.h>
#include "BindingUtil.h"

#include "Config.h"
#include "Debug.h"
#include "Core/ContextInterface.h"
#include "Core/Interfaces.h"
#include "Core/ElementInterface.h"



namespace Rocket {
namespace Core {
namespace Squirrel {




Module* Module::s_pInstance = 0x0;


Module::Module(HSQUIRRELVM vm, bool useNamespace) :
	mUseNamespace(useNamespace),
	mVM(vm),
	mVMCreated(false),
	mInitialized(false)
{
	s_pInstance = this;
}

Module::~Module()
{
}

Module& Module::instance()
{
	ROCKETSQUIRREL_ASSERT(s_pInstance != 0x0);
	return *s_pInstance;
}

bool Module::isUsingNamespace() const
{
	return mUseNamespace;
}

HSQUIRRELVM Module::getSquirrelVM() const
{
	return mVM;
}

void Module::OnInitialise()
{
	ROCKETSQUIRREL_ASSERT(mInitialized == false);

	if (!mVM)
	{
		mVM = sq_open(1024);

		sq_setcompilererrorhandler(mVM, &CompileErrorFunc);
		sq_setprintfunc(mVM, &PrintFunc, &PrintFunc);

		sq_pushroottable(mVM);
		sq_newclosure(mVM, &PrintRuntimeError, 0);
		sq_seterrorhandler(mVM);
		sq_pop(mVM, 1);

		mVMCreated = true;
	}

	//Register Core interfaces
	RegisterSquirrelInterfaces(mVM);
	ContextInterface::Register(mVM);
	ElementInterface::Register(mVM);

	ContextInterface::InitialiseRocketInterface();

	mInitialized = true;
}

void Module::OnShutdown()
{
	ROCKETSQUIRREL_ASSERT(mInitialized == true);

	if (mVM && mVMCreated)
	{
		sq_close(mVM);
	}

	mInitialized = false;
}



		






}
}
}
