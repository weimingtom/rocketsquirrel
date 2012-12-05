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

#include "RocketSquirrel/Core/Module.h"
#include <Rocket/Core.h>
#include "../BindingUtil.h"

#include "Config.h"
#include "../Debug.h"
#include "ContextInterface.h"
#include "Interfaces.h"
#include "ElementInterface.h"
#include "RocketSquirrel/Core/ScriptInterface.h"
#include "EventInterface.h"
#include "ElementCaster.h"



namespace Rocket {
namespace Core {
namespace Squirrel {




Module* Module::s_pInstance = 0x0;



class DefaultScriptInterface : public ScriptInterface
{
public:

	virtual bool OnInitialization()
	{
		mAttachSquirrelFunctions = true;
		mUseNamespace = true;

		return true;
	}

	virtual void OnDestroy()
	{
		return;
	}
};



Module::Module(ScriptInterface* pScriptInterface) :
	mInitialized(false),
	m_pScriptInterface(pScriptInterface)
{
	s_pInstance = this;

	if (!m_pScriptInterface)
	{
		m_pScriptInterface = new DefaultScriptInterface();
	}


	getScriptInterface().AddBindFunction(&BindKeyMap);
	getScriptInterface().AddBindFunction(&BindSquirrelInterfaces);
	getScriptInterface().AddBindFunction(&EventInterface::Bind);
	getScriptInterface().AddBindFunction(&ContextInterface::Bind);
	getScriptInterface().AddBindFunction(&ElementCaster::Bind);
	getScriptInterface().AddBindFunction(&ElementInterface::Bind);

}

Module::~Module()
{
	if (m_pScriptInterface)
	{
		m_pScriptInterface->Release();
	}
	s_pInstance = 0x0;
}

Module& Module::instance()
{
	ROCKETSQUIRREL_ASSERT(s_pInstance != 0x0);
	return *s_pInstance;
}

void Module::OnInitialise()
{
	ROCKETSQUIRREL_ASSERT(mInitialized == false);

	bool result = getScriptInterface().Initialize();

	ROCKETSQUIRREL_ASSERT(result);

	EventInterface::InitialiseRocketInterface();
	ElementInterface::InitialiseRocketInterface();
	ContextInterface::InitialiseRocketInterface();

	mInitialized = true;
}

void Module::OnShutdown()
{
	ROCKETSQUIRREL_ASSERT(mInitialized == true);

	getScriptInterface().Destroy();

	mInitialized = false;
}

ScriptInterface& Module::getScriptInterface() const
{
	ROCKETSQUIRREL_ASSERT(m_pScriptInterface != 0x0);
	return *m_pScriptInterface;
}

bool Module::isInit() const
{
	return mInitialized;
}


		






}
}
}
