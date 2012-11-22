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

#include "RocketSquirrel.h"

#include <sqbind/sqbBind.h>
#include <sqbind/sqbBindMacros.h>
#include <sqbind/sqbClassDefinition.h>
#include <sqbind/SquirrelBind.h>

#include "../BindingUtil.h"
#include "../Debug.h"

#include "DictionaryInterface.h"
#include "VariantInterface.h"

#include "VectorInterface.h"

SQBIND_DECLARE_CLASS(Rocket::Core::String);

SQBIND_DECLARE_CLASS(Rocket::Core::StringList);

SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::VectorInterface<Rocket::Core::StringList>);

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2f);

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2i);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourf);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourb);

SQBIND_DECLARE_CLASS(Rocket::Core::URL);

SQBIND_DECLARE_ENUM(Rocket::Core::Log::Type);


namespace Rocket {
namespace Core {
namespace Squirrel {







static void Log(Rocket::Core::Log::Type level, const char* message)
{	
	Core::Log::Message(level, "%s", message);
}

static SQInteger Vector2fConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 3)
	{
		Rocket::Core::Vector2f* pVec2f = squirrelNewInstance<Rocket::Core::Vector2f>(v);

		if (pVec2f)
		{
			sq_getfloat(v, 2, &pVec2f->x);
			sq_getfloat(v, 3, &pVec2f->y);
		}

		return 1;
	}

	return sqb::ClassDefinition<Rocket::Core::Vector2f>::DefaultConstructor(v);
}

static SQInteger Vector2iConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 4)
	{
		Rocket::Core::Vector2i* pVec2i = squirrelNewInstance<Rocket::Core::Vector2i>(v);

		if (pVec2i)
		{
			sq_getinteger(v, 2, &pVec2i->x);
			sq_getinteger(v, 3, &pVec2i->y);
		}

		return 1;
	}

	return sqb::ClassDefinition<Rocket::Core::Vector2i>::DefaultConstructor(v);
}

static SQInteger ColourfConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 4)
	{
		Rocket::Core::Colourf* pColf = squirrelNewInstance<Rocket::Core::Colourf>(v);

		if (pColf)
		{
			sq_getfloat(v, 2, &pColf->red);
			sq_getfloat(v, 3, &pColf->green);
			sq_getfloat(v, 4, &pColf->blue);
			sq_getfloat(v, 5, &pColf->alpha);
		}

		return 1;
	}

	return sqb::ClassDefinition<Rocket::Core::Colourf>::DefaultConstructor(v);
}

static SQInteger ColourbConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 3)
	{
		Rocket::Core::Colourb* pColb = squirrelNewInstance<Rocket::Core::Colourb>(v);

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

		return 1;
	}

	return sqb::ClassDefinition<Rocket::Core::Colourb>::DefaultConstructor(v);
}

static SQInteger URLConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 2)
	{
		Rocket::Core::URL* pURL = squirrelNewInstance<Rocket::Core::URL>(v);

		if (pURL)
		{
			const SQChar* url;
			if (SQ_SUCCEEDED(sq_getstring(v, 2, &url)))
			{
				pURL->SetURL(url);
			}
		}

		return 1;
	}	

	return sqb::ClassDefinition<Rocket::Core::URL>::DefaultConstructor(v);
}


static SQInteger StringConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 2)
	{
		Rocket::Core::String* pStr = squirrelNewInstance<Rocket::Core::String>(v);

		Rocket::Core::Variant variant;

		switch (sq_gettype(v, 2))
		{
		case OT_STRING:
			{
				const SQChar* str;
				if (SQ_SUCCEEDED(sq_getstring(v, 2, &str)))
				{
					variant.Set(str);
				}
			} break;
		case OT_INTEGER:
			{
				SQInteger inte;
				if (SQ_SUCCEEDED(sq_getinteger(v, 2, &inte)))
				{
					variant.Set(inte);
				}
			} break;
		case OT_FLOAT:
			{
				float f;
				if (SQ_SUCCEEDED(sq_getfloat(v, 2, &f)))
				{
					variant.Set(f);
				}
			} break;
		}

		pStr->Append(variant.Get<Rocket::Core::String>().CString());

		return 1;
	}	

	return sqb::ClassDefinition<Rocket::Core::String>::DefaultConstructor(v);
}

void RegisterSquirrelInterfaces(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);


	//RocketString
	sqb::ClassDefinition<Rocket::Core::String> cStr(vm, -1, _SC("RocketString"));

	cStr.Constructor(&StringConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("x")));

	cStr.ClassFunction<Rocket::Core::String& (Rocket::Core::String::*)(const char* assign)>(&Rocket::Core::String::operator=, _SC("Set"));
	cStr.ClassFunction(&Rocket::Core::String::CString, _SC("_tostring"));



	//StringList
	sqb::ClassDefinition<VectorInterface<Rocket::Core::StringList>> cVec(vm, -1, _SC("StringList"));

	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::Contains, _SC("Contains"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::SetItem, _SC("_set"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::GetItem, _SC("_get"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::PushBack, _SC("append"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::PushBack, _SC("push"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::Size, _SC("len"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::DelItem, _SC("remove"));

	//Vector2f
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


	//Vector2i
	sqb::ClassDefinition<Rocket::Core::Vector2i> cV2i(vm, -1, _SC("Vector2i"));

	cV2i.Constructor(&Vector2iConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xii")));

	cV2i.Variable(&Rocket::Core::Vector2i::x, _SC("x"));
	cV2i.Variable(&Rocket::Core::Vector2i::y, _SC("y"));
	cV2i.ClassFunction(&Rocket::Core::Vector2i::operator*, _SC("_mul"));
	cV2i.ClassFunction(&Rocket::Core::Vector2i::operator/, _SC("_div"));
	cV2i.ClassFunction(&Rocket::Core::Vector2i::operator+, _SC("_add"));
	cV2i.ClassFunction<Rocket::Core::Vector2i (Rocket::Core::Vector2i::*)(const Rocket::Core::Vector2i&) const>(&Rocket::Core::Vector2i::operator-, _SC("_sub"));
	cV2i.ClassFunction(&Rocket::Core::Vector2i::operator==, _SC("_cmp"));


	//Colourf
	sqb::ClassDefinition<Rocket::Core::Colourf> cCf(vm, -1, _SC("Colourf"));

	cCf.Constructor(&ColourfConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xffff")));

	cCf.Variable(&Rocket::Core::Colourf::red, _SC("red"));
	cCf.Variable(&Rocket::Core::Colourf::green, _SC("green"));
	cCf.Variable(&Rocket::Core::Colourf::blue, _SC("blue"));
	cCf.Variable(&Rocket::Core::Colourf::alpha, _SC("alpha"));
	cCf.ClassFunction(&Rocket::Core::Colourf::operator==, _SC("_cmp"));



	//Colourb
	sqb::ClassDefinition<Rocket::Core::Colourb> cCb(vm, -1, _SC("Colourb"));

	cCb.Constructor(&ColourbConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xiiii")));

	cCb.Variable(&Rocket::Core::Colourb::red, _SC("red"));
	cCb.Variable(&Rocket::Core::Colourb::green, _SC("green"));
	cCb.Variable(&Rocket::Core::Colourb::blue, _SC("blue"));
	cCb.Variable(&Rocket::Core::Colourb::alpha, _SC("alpha"));
	cCb.ClassFunction(&Rocket::Core::Colourb::operator==, _SC("_cmp"));
	cCb.ClassFunction(&Rocket::Core::Colourb::operator+, _SC("_add"));
	cCb.ClassFunction<Rocket::Core::Colourb (Rocket::Core::Colourb::*)(float) const>(&Rocket::Core::Colourb::operator*, _SC("_mul"));


	//URL
	sqb::ClassDefinition<Rocket::Core::URL> cURL(vm, -1, _SC("URL"));

	cURL.Constructor(&URLConstructor, sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xs")));

	cURL.ClassFunction(&Rocket::Core::URL::ClearParameters, _SC("ClearParameters"));


	//Log
	sqb::Bind::BindFunction(vm, -1, &Log, _SC("Log"));


	//LogType
	sqb::ClassDefinition<Rocket::Core::Log::Type> cLT(vm, -1, _SC("LogType"));
	cLT.EnumEntry(Rocket::Core::Log::LT_ALWAYS, "always");
	cLT.EnumEntry(Rocket::Core::Log::LT_ERROR, "error");
	cLT.EnumEntry(Rocket::Core::Log::LT_WARNING, "warning");
	cLT.EnumEntry(Rocket::Core::Log::LT_INFO, "info");
	cLT.EnumEntry(Rocket::Core::Log::LT_DEBUG, "debug");

	VariantInterface::Bind(vm);
	DictionaryInterface::Bind(vm);


	sq_poptop(vm);

	return;
}













}
}
}