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

#include "ElementDocument.h"
#include "../BindingUtil.h"
#include <squirrel.h>
#include "RocketSquirrel.h"
#include "ElementWrapperDerived.h"
#include "../Debug.h"
#include "RocketSquirrel/Core/ScriptInterface.h"
#include <Rocket/Core/FileInterface.h>
#include "../SquirrelScript.h"


namespace Rocket {
namespace Core {
namespace Squirrel {





ElementDocument::ElementDocument(const String& tag, ScriptInterface* pScriptInterface) :
	Rocket::Core::ElementDocument(tag),
	m_pScriptInterface(pScriptInterface)
{

}

ElementDocument::~ElementDocument()
{
}


void ElementDocument::LoadScript(Rocket::Core::Stream* stream, const Rocket::Core::String& source_name) 
{
	if (m_pScriptInterface)
	{
		m_pScriptInterface->LoadScript(this, stream, source_name);
	}
	else
	{
		Rocket::Core::String buffer;
		stream->Read(buffer, stream->Length());

		Rocket::Core::String moduleName = Rocket::Core::String(source_name).Replace("/", "_");
		moduleName = moduleName.Replace("\\", "_");
		moduleName = moduleName.Replace(".nut", "");

		HSQUIRRELVM vm = Module::instance().getScriptInterface().getSquirrelVM();

		SQRESULT sqr;
		
		SquirrelScript script(buffer, source_name);


		script.Compile(vm, false);

		SQInteger i = sq_gettop(vm);

		Module::instance().getScriptInterface().PushDocumentTable(vm, this);
		sqr = sq_bindenv(vm, i);

		ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

		sq_pushroottable(vm);
		script.Run(vm);

		sq_pop(vm, i);


	}
}





}
}
}
