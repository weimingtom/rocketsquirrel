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

#include "RocketSquirrel/Core/ScriptInterface.h"
#include "../BindingUtil.h"
#include <Rocket/Core.h>


namespace Rocket {
namespace Core {
namespace Squirrel {





/*void ScriptInterface::LoadScript(ElementDocument* document, Rocket::Core::Stream* stream, const Rocket::Core::String& source_name)
{

	return;
}*/
	
ScriptInterface::ScriptInterface() :
	mAttachErrorCallbacks(true),
	mUseNamespace(true)
{

}

ScriptInterface::~ScriptInterface()
{
}

HSQUIRRELVM ScriptInterface::OpenVM()
{
	return sq_open(1024);
}

void ScriptInterface::CloseVM()
{
	sq_close(mVM);
}

void ScriptInterface::Release()
{
	delete this;
}

void ScriptInterface::PrintError(const Rocket::Core::String& text)
{
	Rocket::Core::Log::Message(Rocket::Core::Log::LT_WARNING, "%s", text.CString());
}

void ScriptInterface::Print(const Rocket::Core::String& text)
{
	Rocket::Core::Log::Message(Rocket::Core::Log::LT_INFO, "%s", text.CString());
}

void ScriptInterface::ReportCompilationError(const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
{
	return;
}

bool ScriptInterface::Initialize()
{
	mVM = OpenVM();

	if (mAttachErrorCallbacks)
	{
		sq_setcompilererrorhandler(mVM, &CompileErrorFunc);
		sq_setprintfunc(mVM, &PrintFunc, &PrintErrorFunc);

		sq_pushroottable(mVM);
		sq_newclosure(mVM, &PrintRuntimeError, 0);
		sq_seterrorhandler(mVM);
		sq_poptop(mVM);
	}

	return OnInitialization();
}

void ScriptInterface::Destroy()
{
}

bool ScriptInterface::isUsingNamespace() const
{
	return mUseNamespace;
}

HSQUIRRELVM ScriptInterface::getSquirrelVM() const
{
	return mVM;
}






}
}
}