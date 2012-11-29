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

#ifndef __ROCKETSQUIRREL_SCRIPTINTERFACE_INCLUDED
#define __ROCKETSQUIRREL_SCRIPTINTERFACE_INCLUDED

#include <squirrel.h>
#include <RocketSquirrel.h>
#include <vector>

namespace Rocket {
namespace Core {
namespace Squirrel {



typedef void (*ScriptBindFunction)(HSQUIRRELVM vm);


class ROCKETSQUIRRELDLL_API ScriptInterface
{
private:

	/*! List of the functions needed to bind RocketSquirrel into a VM*/
	std::vector<ScriptBindFunction> mBindingFunctions;

protected:

	HSQUIRRELVM mVM;
	bool mAttachSquirrelFunctions;
	bool mUseNamespace;

public:

	ScriptInterface();
	virtual ~ScriptInterface();

	/*!
	 * Should return a valid Squirrel VM doesn't matter if
	 * it's freshly created or previously created by your own code
	 * RocketSquirrel will bind the interfaces into that VM
	 *
	 * If you dont replace this method then a default VM will be created
	 */
	virtual HSQUIRRELVM OpenVM();

	/*!
	 * Called on Destroy, it expects to call sq_close on the Virtual Machine
	 * But you dont have to close if you still needing it, by default it calls sq_close(mVM);
	 */
	virtual void CloseVM();

	/*! 
	 * Called at Core::Module deletion 
	 */
	virtual void Release();

	/*!
	 * Called on initialization (tryggered by Rocket::Core::Initialise)
	 */
	virtual bool OnInitialization() = 0;

	/*!
	 * Called on Rocket shutdown
	 */
	virtual void OnDestroy() = 0;

	/*!
	 * Reports a compilation error
	 * You're supoused to call this from your C++ squirrel compilation error function
	 * to enable logging/diplaying of errors
	 * By default if mAttachSquirrelFunctions is true this will be called internally
	 */
	virtual void ReportCompilationError(const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column);

	/*!
	 * Call this from your C++ squirrel print error function
	 * By default if mAttachSquirrelFunctions is true this will be called internally
	 */
	virtual void PrintError(const Rocket::Core::String& text);

	/*!
	 * Call this from your C++ squirrel print function
	 * By default if mAttachSquirrelFunctions is true this will be called internally
	 */
	virtual void Print(const Rocket::Core::String& text);

	/*!
	 * Bindes all the interfaces into the selected VM (no the internal mVM)
	 * This is called internally (BindVM(mVM)) on initialization
	 * but it could be usefull if you want to bind other VM
	 */
	void BindIntoSquirrelVM(HSQUIRRELVM vm) const;

	bool isUsingNamespace() const;
	HSQUIRRELVM getSquirrelVM() const;

	void AddBindFunction(ScriptBindFunction function);
	void RemoveBindFunction(ScriptBindFunction function);

	bool Initialize();
	void Destroy();
};







}
}
}





#endif