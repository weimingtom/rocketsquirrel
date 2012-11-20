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


#include <Rocket/Core/URL.h>
#include <Rocket/Core/Log.h>
#include <Rocket/Core/Dictionary.h>
#include <vector>
#include <squirrel.h>

#include <iostream>


#include <sqbind/sqbBind.h>
#include <sqbind/sqbBindMacros.h>
#include <sqbind/sqbClassDefinition.h>
#include <sqbind/SquirrelBind.h>

#include "BindingUtil.h"

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2f);

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2i);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourf);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourb);

SQBIND_DECLARE_CLASS(Rocket::Core::URL);

SQBIND_DECLARE_ENUM(Rocket::Core::Log::Type);


namespace Rocket {
	namespace Squirrel {


		HSQUIRRELVM vm;

		static void Log(Rocket::Core::Log::Type level, const char* message)
		{	
			Core::Log::Message(level, "%s", message);
		}

		static SQInteger Vector2fConstructor(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v);

			if (nargs >= 3)
			{
				Rocket::Core::Vector2f* pVec2f = squirrelGetInstanceObj<Rocket::Core::Vector2f>(v);

				if (pVec2f)
				{
					sq_getfloat(v, 2, &pVec2f->x);
					sq_getfloat(v, 3, &pVec2f->y);
				}
			}

			sq_pushinteger(v,nargs);

			return 1;
		}

		static SQInteger Vector2iConstructor(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v);

			if (nargs >= 4)
			{
				Rocket::Core::Vector2i* pVec2i = squirrelGetInstanceObj<Rocket::Core::Vector2i>(v);

				if (pVec2i)
				{
					sq_getinteger(v, 2, &pVec2i->x);
					sq_getinteger(v, 3, &pVec2i->y);
				}
			}

			sq_pushinteger(v,nargs);

			return 1;
		}

		static SQInteger ColourfConstructor(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v);

			if (nargs >= 4)
			{
				Rocket::Core::Colourf* pColf = squirrelGetInstanceObj<Rocket::Core::Colourf>(v);

				if (pColf)
				{
					sq_getfloat(v, 2, &pColf->red);
					sq_getfloat(v, 3, &pColf->green);
					sq_getfloat(v, 4, &pColf->blue);
					sq_getfloat(v, 5, &pColf->alpha);
				}
			}

			sq_pushinteger(v,nargs);

			return 1;
		}

		static SQInteger ColourbConstructor(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v);

			if (nargs >= 3)
			{
				Rocket::Core::Colourb* pColb = squirrelGetInstanceObj<Rocket::Core::Colourb>(v);

				if (pColb)
				{
					SQInteger red, green, blue, alpha;

					sq_getinteger(v, 2, &red);
					sq_getinteger(v, 3, &green);
					sq_getinteger(v, 4, &blue);
					sq_getinteger(v, 5, &alpha);

					pColb->red = red;
					pColb->green = green;
					pColb->blue = blue;
					pColb->alpha = alpha;
				}
			}

			sq_pushinteger(v,nargs);

			return 1;
		}

		static SQInteger URLConstructor(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v);

			if (nargs >= 2)
			{
				Rocket::Core::URL* pURL = squirrelGetInstanceObj<Rocket::Core::URL>(v);

				if (pURL)
				{
					const SQChar* url;
					if (SQ_SUCCEEDED(sq_getstring(v, 2, &url)))
					{
						//pURL->SetURL(url);
					}
				}
			}

			sq_pushinteger(v,nargs);

			return 1;
		}

		void RegisterSquirrelInterfaces()
		{
			vm = sq_open(1024);

			sq_setcompilererrorhandler(vm, &squirrelCompileErrorFunc);
			sq_setprintfunc(vm, &squirrelPrintFunc, &squirrelPrintFunc);


			sq_pushroottable(vm);
			sq_newclosure(vm, &squirrelPrintRuntimeError, 0);
			sq_seterrorhandler(vm);
			sq_pop(vm, 1);



			//Vector2f
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::Vector2f> cV2f(vm, -1, _SC("Vector2f"));

			cV2f.Constructor(&Vector2fConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xff")));

			cV2f.Variable(&Rocket::Core::Vector2f::x, _SC("x"));
			cV2f.Variable(&Rocket::Core::Vector2f::y, _SC("y"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::operator*, _SC("_mul"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::operator/, _SC("_div"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::operator+, _SC("_add"));
			cV2f.ClassFunction<Rocket::Core::Vector2f (Rocket::Core::Vector2f::*)(const Rocket::Core::Vector2f&) const>(&Rocket::Core::Vector2f::operator-, _SC("_sub"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::operator==, _SC("_cmp"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::DotProduct, _SC("DotProduct"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::Rotate, _SC("Rotate"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::Normalise, _SC("Normalise"));
			cV2f.ClassFunction(&Rocket::Core::Vector2f::Magnitude, _SC("Magnitude"));

			sq_poptop(vm);


			//Vector2i
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::Vector2i> cV2i(vm, -1, _SC("Vector2i"));

			cV2i.Constructor(&Vector2iConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xii")));

			cV2i.Variable(&Rocket::Core::Vector2i::x, _SC("x"));
			cV2i.Variable(&Rocket::Core::Vector2i::y, _SC("y"));
			cV2i.ClassFunction(&Rocket::Core::Vector2i::operator*, _SC("_mul"));
			cV2i.ClassFunction(&Rocket::Core::Vector2i::operator/, _SC("_div"));
			cV2i.ClassFunction(&Rocket::Core::Vector2i::operator+, _SC("_add"));
			cV2i.ClassFunction<Rocket::Core::Vector2i (Rocket::Core::Vector2i::*)(const Rocket::Core::Vector2i&) const>(&Rocket::Core::Vector2i::operator-, _SC("_sub"));
			cV2i.ClassFunction(&Rocket::Core::Vector2i::operator==, _SC("_cmp"));

			sq_poptop(vm);


			//Colourf
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::Colourf> cCf(vm, -1, _SC("Colourf"));

			cCf.Constructor(&ColourfConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xffff")));

			cCf.Variable(&Rocket::Core::Colourf::red, _SC("red"));
			cCf.Variable(&Rocket::Core::Colourf::green, _SC("green"));
			cCf.Variable(&Rocket::Core::Colourf::blue, _SC("blue"));
			cCf.Variable(&Rocket::Core::Colourf::alpha, _SC("alpha"));
			cCf.ClassFunction(&Rocket::Core::Colourf::operator==, _SC("_cmp"));

			sq_poptop(vm);



			//Colourb
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::Colourb> cCb(vm, -1, _SC("Colourb"));

			//cCb.Constructor(&ColourbConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xiiii")));

			cCb.Variable(&Rocket::Core::Colourb::red, _SC("red"));
			cCb.Variable(&Rocket::Core::Colourb::green, _SC("green"));
			cCb.Variable(&Rocket::Core::Colourb::blue, _SC("blue"));
			cCb.Variable(&Rocket::Core::Colourb::alpha, _SC("alpha"));
			cCb.ClassFunction(&Rocket::Core::Colourb::operator==, _SC("_cmp"));
			cCb.ClassFunction(&Rocket::Core::Colourb::operator+, _SC("_add"));
			cCb.ClassFunction<Rocket::Core::Colourb (Rocket::Core::Colourb::*)(float) const>(&Rocket::Core::Colourb::operator*, _SC("_mul"));

			sq_poptop(vm);


			//URL
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::URL> cURL(vm, -1, _SC("URL"));

			cURL.Constructor(&URLConstructor, sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xs")));

			cURL.ClassFunction(&Rocket::Core::URL::ClearParameters, _SC("ClearParameters"));


			sq_poptop(vm);


			//Log
			sq_pushroottable(vm);

			sqb::Bind::BindFunction(vm, -1, &Log, _SC("Log"));

			sq_poptop(vm);

			//LogType
			sq_pushroottable(vm);

			sqb::ClassDefinition<Rocket::Core::Log::Type> cLT(vm, -1, _SC("LogType"));
			cLT.EnumEntry(Rocket::Core::Log::LT_ALWAYS, "always");
			cLT.EnumEntry(Rocket::Core::Log::LT_ERROR, "error");
			cLT.EnumEntry(Rocket::Core::Log::LT_WARNING, "warning");
			cLT.EnumEntry(Rocket::Core::Log::LT_INFO, "info");
			cLT.EnumEntry(Rocket::Core::Log::LT_DEBUG, "debug");

			sq_poptop(vm);

			new Rocket::Core::Colourb();

			Rocket::Core::URL* url = new Rocket::Core::URL();
			url->SetURL("asdasd");

			return;
		}



		void TestSquirrel()
		{
		}


		void TestInsterfaces()
		{
			std::string script = " local v = Vector2f(); local v2 = Vector2f(); print(v.DotProduct(v2)); v.x = \"asdasd\"; ";

			sq_compilebuffer(vm, script.c_str(), script.size(), "Script.nut", true);

			compileNutFile(vm, "./testingscripts/Interfaces.nut");
  
			sq_pushroottable(vm);

			sq_call(vm, 1, false, true);

			return;
		}






	}
}