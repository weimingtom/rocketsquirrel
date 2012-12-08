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

#ifndef __SQUIRREL_GAME
#define __SQUIRREL_GAME


#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include <RocketSquirrel/Core/Module.h>
#include <RocketSquirrel/Core/ScriptInterface.h>
#include <Rocket/Core/String.h>
#include "Config.h"
#include "Shell.h"


class SquirrelGame
{
private:

	HSQUIRRELVM vm;

	static SQInteger file_lexfeedASCII(SQUserPointer file)
	{
		int ret;
		char c;
		if( ( ret=fread(&c,sizeof(c),1,(FILE *)file )>0) )
			return c;
		return 0;
	}

	static SQRESULT CompileNutFile(HSQUIRRELVM v, const char *filename)
	{
		SQRESULT r = -1;

		FILE *f=fopen(filename,"rb");
		if(f)
		{
			r = sq_compile(v,file_lexfeedASCII, f, filename, 1);

			fclose(f);
		}

		return r;
	}

	static const char* AssetDir(const char* path)
	{
		static Rocket::Core::String fullPath;

		fullPath.Clear();
		fullPath += ROCKETSQUIRREL_SAMPLE_ASSETS;
		fullPath += "/";
		fullPath += path;

		return fullPath.CString();
	}

	void ExecuteScript(const char* path)
	{
		CompileNutFile(vm, AssetDir(path));

		SQInteger i = sq_gettop(vm);

		sq_pushroottable(vm);

		sq_call(vm, 1, false, true);

		sq_pop(vm, i);
	}

	Rocket::Core::Context* context;

	float delta;

public:

	/*AKA called once each loop in the game loop*/
	void Tick()
	{
		sq_pushroottable(vm);

		sq_pushstring(vm, _SC("Tick"), -1);
		sq_get(vm, -2);
		sq_pushroottable(vm);
		sq_call(vm, 1, false, true);

		sq_poptop(vm);
	}

	void initialize()
	{
		using Rocket::Core::Squirrel::Module;

		Shell::LoadFonts(AssetDir(""));

		//Now lets get the VM that rocketsquirrel created for us
		vm = Module::instance().getScriptInterface().getSquirrelVM();

		/*bind the elapsed time*/
		sq_pushroottable(vm);
		sqb::Bind::BindFunction(vm, -1, &Shell::GetElapsedTime, _SC("GetElapsedTime"));

		/*Bind the close WIndow function*/
		sqb::Bind::BindFunction(vm, -1, &Shell::CloseWindow, _SC("CloseWindow"));

		/*Bind the assetsdir function*/
		sqb::Bind::BindFunction(vm, -1, &AssetDir, _SC("AssetDir"));

		sq_poptop(vm);

		/*Lets call the initialization script*/
		ExecuteScript("scripts/Initialize.nut");

		/*Get the context crreated by squirrel*/
		context = Rocket::Core::GetContext("SquirrelGame");
		assert(context != NULL);

		Rocket::Debugger::Initialise(context);
		Input::SetContext(context);
	}

	void destroy()
	{
		ExecuteScript("scripts/Destroy.nut");
	}

};



#endif