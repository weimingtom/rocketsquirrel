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
#include "../NamespaceHelper.h"
#include <Rocket/Core.h>
#include "../Debug.h"


namespace Rocket {
namespace Core {
namespace Squirrel {





/*void ScriptInterface::LoadScript(ElementDocument* document, Rocket::Core::Stream* stream, const Rocket::Core::String& source_name)
{

	return;
}*/
	
ScriptInterface::ScriptInterface() :
	mAttachSquirrelFunctions(true),
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
	sq_collectgarbage(mVM);
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

	if (mAttachSquirrelFunctions)
	{
		sq_setcompilererrorhandler(mVM, &CompileErrorFunc);
		sq_setprintfunc(mVM, &PrintFunc, &PrintErrorFunc);

		sq_pushroottable(mVM);
		sq_newclosure(mVM, &PrintRuntimeError, 0);
		sq_seterrorhandler(mVM);
		sq_poptop(mVM);
	}

	BindIntoSquirrelVM(mVM);

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

void ScriptInterface::BindIntoSquirrelVM(HSQUIRRELVM vm) const
{
	sq_pushroottable(vm);
	NamespaceHelper::create(vm, "Rocket");
	sq_poptop(vm);

	Rocket::Core::Log::Message(Rocket::Core::Log::LT_INFO, "Binding libRocket into Squirrel VM (%d)", vm);
	for (size_t i = 0; i < mBindingFunctions.size(); i++)
	{
		mBindingFunctions[i](mVM);
	}

	//now lets create the document tables array
	sq_pushroottable(vm);

	NamespaceHelper::switchTo(vm, "Rocket");

	sq_pushstring(vm, _SC("__docTables"), -1);
	sq_newtable(vm);
	sq_newslot(vm, -3, true);

	sq_pop(vm, 2);
}

void ScriptInterface::PushDocumentTable(HSQUIRRELVM vm, Rocket::Core::ElementDocument* pDoc)
{
	SQInteger i = -1;

	SQRESULT sqr;

	//sq_pushroottable(vm);

	NamespaceHelper::switchTo(vm, "Rocket");

	sq_pushstring(vm, _SC("__docTables"), -1);
	sqr = sq_get(vm, -2);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	sq_pushuserpointer(vm, (SQUserPointer)pDoc);
	sqr = sq_get(vm, -2);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));

	//sq_pop(vm, 3);
}

void ScriptInterface::AddBindFunction(ScriptBindFunction function)
{
	mBindingFunctions.push_back(function);
}

void ScriptInterface::RemoveBindFunction(ScriptBindFunction function)
{
	//TODO
}






}
}
}