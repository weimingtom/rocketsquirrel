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

#include "Interfaces.h"
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
#include "../NamespaceHelper.h"



class DummyInputClass {
public:
	DummyInputClass() {};

	int dummyVal;

};

SQBIND_DECLARE_CLASS(DummyInputClass);


namespace Rocket {
namespace Core {
namespace Squirrel {







static void Log(int intLevel, const char* message)
{	
	using Rocket::Core::Log;
	
	Log::Type level;
	
	switch (intLevel)
	{
	case Log::LT_ALWAYS: level = Log::LT_ALWAYS; break;
	case Log::LT_ERROR: level = Log::LT_ERROR; break;
	case Log::LT_WARNING: level = Log::LT_WARNING; break;
	case Log::LT_INFO: level = Log::LT_INFO; break;
	case Log::LT_DEBUG: level = Log::LT_DEBUG; break;
	}
	
	Core::Log::Message(level, "%s", message);
}

static SQInteger Vector2fConstructor(HSQUIRRELVM v)
{
	SQInteger nargs = sq_gettop(v);

	if (nargs >= 3)
	{
		Rocket::Core::Vector2f* pVec2f = NewInstance<Rocket::Core::Vector2f>(v);

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

	if (nargs >= 3)
	{
		Rocket::Core::Vector2i* pVec2i = NewInstance<Rocket::Core::Vector2i>(v);

		if (pVec2i)
		{
			SQInteger x, y;
			
			sq_getinteger(v, 2, &x);
			sq_getinteger(v, 3, &y);
			
			pVec2i->x = x;
			pVec2i->y = y;
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
		Rocket::Core::Colourf* pColf = NewInstance<Rocket::Core::Colourf>(v);

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
		Rocket::Core::Colourb* pColb = NewInstance<Rocket::Core::Colourb>(v);

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
		Rocket::Core::URL* pURL = NewInstance<Rocket::Core::URL>(v);

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
		Rocket::Core::String* pStr = NewInstance<Rocket::Core::String>(v);

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
					variant.Set((int)inte);
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

void BindSquirrelInterfaces(HSQUIRRELVM vm)
{

	//Namespace Rocket
	sq_pushroottable(vm);	
	NamespaceHelper::switchTo(vm, "Rocket");


	//RocketString
	sqb::ClassDefinition<Rocket::Core::String> cStr(vm, -1, _SC("String"));

	cStr.Constructor(&StringConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("x")));

	typedef Rocket::Core::String& (Rocket::Core::String::* AppendType)(const char* assign);

	cStr.ClassFunction<AppendType>(&Rocket::Core::String::operator=, _SC("Set"));
	cStr.ClassFunction(&Rocket::Core::String::CString, _SC("_tostring"));
	cStr.ClassFunction<AppendType>(&Rocket::Core::String::operator+=, _SC("Append"));
	cStr.ClassFunction<AppendType>(&Rocket::Core::String::operator+=, _SC("_add"));
	cStr.ClassFunction(&Rocket::Core::String::Clear, _SC("Clear"));



	//StringList
	sqb::ClassDefinition<VectorInterface<Rocket::Core::StringList>> cVec(vm, -1, _SC("StringList"));

	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::Contains, _SC("Contains"));
	cVec.ClassFunction(&VectorInterface<Rocket::Core::StringList>::SetItem, _SC("_set"));
	cVec.NativeClassFunction(&VectorInterface<Rocket::Core::StringList>::GetItem, _SC("_get"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xi")));
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
	cV2f.ClassFunction(&Rocket::Core::Vector2f::operator==, _SC("Equal"));
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
	cV2i.ClassFunction(&Rocket::Core::Vector2i::operator==, _SC("Equal"));


	//Colourf
	sqb::ClassDefinition<Rocket::Core::Colourf> cCf(vm, -1, _SC("Colourf"));

	cCf.Constructor(&ColourfConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xffff")));

	cCf.Variable(&Rocket::Core::Colourf::red, _SC("red"));
	cCf.Variable(&Rocket::Core::Colourf::green, _SC("green"));
	cCf.Variable(&Rocket::Core::Colourf::blue, _SC("blue"));
	cCf.Variable(&Rocket::Core::Colourf::alpha, _SC("alpha"));
	cCf.ClassFunction(&Rocket::Core::Colourf::operator==, _SC("Equal"));



	//Colourb
	sqb::ClassDefinition<Rocket::Core::Colourb> cCb(vm, -1, _SC("Colourb"));

	cCb.Constructor(&ColourbConstructor, sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xiiii")));

	cCb.Variable(&Rocket::Core::Colourb::red, _SC("red"));
	cCb.Variable(&Rocket::Core::Colourb::green, _SC("green"));
	cCb.Variable(&Rocket::Core::Colourb::blue, _SC("blue"));
	cCb.Variable(&Rocket::Core::Colourb::alpha, _SC("alpha"));
	cCb.ClassFunction(&Rocket::Core::Colourb::operator==, _SC("Equal"));
	cCb.ClassFunction(&Rocket::Core::Colourb::operator+, _SC("_add"));
	cCb.ClassFunction<Rocket::Core::Colourb (Rocket::Core::Colourb::*)(float) const>(&Rocket::Core::Colourb::operator*, _SC("_mul"));


	//URL
	sqb::ClassDefinition<Rocket::Core::URL> cURL(vm, -1, _SC("URL"));

	cURL.Constructor(&URLConstructor, sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xs")));

	cURL.ClassFunction(&Rocket::Core::URL::ClearParameters, _SC("ClearParameters"));


	//Log
	sqb::Bind::BindFunction(vm, -1, &Log, _SC("Log"));


	//LogType
	sqb::ClassDefinition<Rocket::Core::Log> cLT(vm, -1, _SC("LogType"));
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

void BindKeyMap(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	class InputEnum
	{
	public:

		sqb::ClassDefinition<DummyInputClass> def;

		InputEnum(HSQUIRRELVM vm) :
			def(vm, -1, _SC("KeyIdentifier"))
		{
		}

		InputEnum& value(const char* name, SQInteger value)
		{
			def.EnumEntry(value, _SC(name));

			return *this;
		}
	};

	InputEnum inputEnum(vm);

	inputEnum
	.value("UNKNOWN", Input::KI_UNKNOWN)
	.value("SPACE", Input::KI_SPACE)
	.value("0", Input::KI_0)
	.value("1", Input::KI_1)
	.value("2", Input::KI_2)
	.value("3", Input::KI_3)
	.value("4", Input::KI_4)
	.value("5", Input::KI_5)
	.value("6", Input::KI_6)
	.value("7", Input::KI_7)
	.value("8", Input::KI_8)
	.value("9", Input::KI_9)
	.value("A", Input::KI_A)
	.value("B", Input::KI_B)
	.value("C", Input::KI_C)
	.value("D", Input::KI_D)
	.value("E", Input::KI_E)
	.value("F", Input::KI_F)
	.value("G", Input::KI_G)
	.value("H", Input::KI_H)
	.value("I", Input::KI_I)
	.value("J", Input::KI_J)
	.value("K", Input::KI_K)
	.value("L", Input::KI_L)
	.value("M", Input::KI_M)
	.value("N", Input::KI_N)
	.value("O", Input::KI_O)
	.value("P", Input::KI_P)
	.value("Q", Input::KI_Q)
	.value("R", Input::KI_R)
	.value("S", Input::KI_S)
	.value("T", Input::KI_T)
	.value("U", Input::KI_U)
	.value("V", Input::KI_V)
	.value("W", Input::KI_W)
	.value("X", Input::KI_X)
	.value("Y", Input::KI_Y)
	.value("Z", Input::KI_Z)
	.value("OEM_1", Input::KI_OEM_1)
	.value("OEM_PLUS", Input::KI_OEM_PLUS)
	.value("OEM_COMMA", Input::KI_OEM_COMMA)
	.value("OEM_MINUS", Input::KI_OEM_MINUS)
	.value("OEM_PERIOD", Input::KI_OEM_PERIOD)
	.value("OEM_2", Input::KI_OEM_2)
	.value("OEM_3", Input::KI_OEM_3)
	.value("OEM_4", Input::KI_OEM_4)
	.value("OEM_5", Input::KI_OEM_5)
	.value("OEM_6", Input::KI_OEM_6)
	.value("OEM_7", Input::KI_OEM_7)
	.value("OEM_8", Input::KI_OEM_8)
	.value("OEM_102", Input::KI_OEM_102)
	.value("NUMPAD0", Input::KI_NUMPAD0)
	.value("NUMPAD1", Input::KI_NUMPAD1)
	.value("NUMPAD2", Input::KI_NUMPAD2)
	.value("NUMPAD3", Input::KI_NUMPAD3)
	.value("NUMPAD4", Input::KI_NUMPAD4)
	.value("NUMPAD5", Input::KI_NUMPAD5)
	.value("NUMPAD6", Input::KI_NUMPAD6)
	.value("NUMPAD7", Input::KI_NUMPAD7)
	.value("NUMPAD8", Input::KI_NUMPAD8)
	.value("NUMPAD9", Input::KI_NUMPAD9)
	.value("NUMPADENTER", Input::KI_NUMPADENTER)
	.value("MULTIPLY", Input::KI_MULTIPLY)
	.value("ADD", Input::KI_ADD)
	.value("SEPARATOR", Input::KI_SEPARATOR)
	.value("SUBTRACT", Input::KI_SUBTRACT)
	.value("DECIMAL", Input::KI_DECIMAL)
	.value("DIVIDE", Input::KI_DIVIDE)
	.value("OEM_NEC_EQUAL", Input::KI_OEM_NEC_EQUAL)
	.value("BACK", Input::KI_BACK)
	.value("TAB", Input::KI_TAB)
	.value("CLEAR", Input::KI_CLEAR)
	.value("RETURN", Input::KI_RETURN)
	.value("PAUSE", Input::KI_PAUSE)
	.value("CAPITAL", Input::KI_CAPITAL)
	.value("KANA", Input::KI_KANA)
	.value("HANGUL", Input::KI_HANGUL)
	.value("JUNJA", Input::KI_JUNJA)
	.value("FINAL", Input::KI_FINAL)
	.value("HANJA", Input::KI_HANJA)
	.value("KANJI", Input::KI_KANJI)
	.value("ESCAPE", Input::KI_ESCAPE)
	.value("CONVERT", Input::KI_CONVERT)
	.value("NONCONVERT", Input::KI_NONCONVERT)
	.value("ACCEPT", Input::KI_ACCEPT)
	.value("MODECHANGE", Input::KI_MODECHANGE)
	.value("PRIOR", Input::KI_PRIOR)
	.value("NEXT", Input::KI_NEXT)
	.value("END", Input::KI_END)
	.value("HOME", Input::KI_HOME)
	.value("LEFT", Input::KI_LEFT)
	.value("UP", Input::KI_UP)
	.value("RIGHT", Input::KI_RIGHT)
	.value("DOWN", Input::KI_DOWN)
	.value("SELECT", Input::KI_SELECT)
	.value("PRINT", Input::KI_PRINT)
	.value("EXECUTE", Input::KI_EXECUTE)
	.value("SNAPSHOT", Input::KI_SNAPSHOT)
	.value("INSERT", Input::KI_INSERT)
	.value("DELETE", Input::KI_DELETE)
	.value("HELP", Input::KI_HELP)
	.value("LWIN", Input::KI_LWIN)
	.value("RWIN", Input::KI_RWIN)
	.value("APPS", Input::KI_APPS)
	.value("POWER", Input::KI_POWER)
	.value("SLEEP", Input::KI_SLEEP)
	.value("WAKE", Input::KI_WAKE)
	.value("F1", Input::KI_F1)
	.value("F2", Input::KI_F2)
	.value("F3", Input::KI_F3)
	.value("F4", Input::KI_F4)
	.value("F5", Input::KI_F5)
	.value("F6", Input::KI_F6)
	.value("F7", Input::KI_F7)
	.value("F8", Input::KI_F8)
	.value("F9", Input::KI_F9)
	.value("F10", Input::KI_F10)
	.value("F11", Input::KI_F11)
	.value("F12", Input::KI_F12)
	.value("F13", Input::KI_F13)
	.value("F14", Input::KI_F14)
	.value("F15", Input::KI_F15)
	.value("F16", Input::KI_F16)
	.value("F17", Input::KI_F17)
	.value("F18", Input::KI_F18)
	.value("F19", Input::KI_F19)
	.value("F20", Input::KI_F20)
	.value("F21", Input::KI_F21)
	.value("F22", Input::KI_F22)
	.value("F23", Input::KI_F23)
	.value("F24", Input::KI_F24)
	.value("NUMLOCK", Input::KI_NUMLOCK)
	.value("SCROLL", Input::KI_SCROLL)
	.value("OEM_FJ_JISHO", Input::KI_OEM_FJ_JISHO)
	.value("OEM_FJ_MASSHOU", Input::KI_OEM_FJ_MASSHOU)
	.value("OEM_FJ_TOUROKU", Input::KI_OEM_FJ_TOUROKU)
	.value("OEM_FJ_LOYA", Input::KI_OEM_FJ_LOYA)
	.value("OEM_FJ_ROYA", Input::KI_OEM_FJ_ROYA)
	.value("LSHIFT", Input::KI_LSHIFT)
	.value("RSHIFT", Input::KI_RSHIFT)
	.value("LCONTROL", Input::KI_LCONTROL)
	.value("RCONTROL", Input::KI_RCONTROL)
	.value("LMENU", Input::KI_LMENU)
	.value("RMENU", Input::KI_RMENU)
	.value("BROWSER_BACK", Input::KI_BROWSER_BACK)
	.value("BROWSER_FORWARD", Input::KI_BROWSER_FORWARD)
	.value("BROWSER_REFRESH", Input::KI_BROWSER_REFRESH)
	.value("BROWSER_STOP", Input::KI_BROWSER_STOP)
	.value("BROWSER_SEARCH", Input::KI_BROWSER_SEARCH)
	.value("BROWSER_FAVORITES", Input::KI_BROWSER_FAVORITES)
	.value("BROWSER_HOME", Input::KI_BROWSER_HOME)
	.value("VOLUME_MUTE", Input::KI_VOLUME_MUTE)
	.value("VOLUME_DOWN", Input::KI_VOLUME_DOWN)
	.value("VOLUME_UP", Input::KI_VOLUME_UP)
	.value("MEDIA_NEXT_TRACK", Input::KI_MEDIA_NEXT_TRACK)
	.value("MEDIA_PREV_TRACK", Input::KI_MEDIA_PREV_TRACK)
	.value("MEDIA_STOP", Input::KI_MEDIA_STOP)
	.value("MEDIA_PLAY_PAUSE", Input::KI_MEDIA_PLAY_PAUSE)
	.value("LAUNCH_MAIL", Input::KI_LAUNCH_MAIL)
	.value("LAUNCH_MEDIA_SELECT", Input::KI_LAUNCH_MEDIA_SELECT)
	.value("LAUNCH_APP1", Input::KI_LAUNCH_APP1)
	.value("LAUNCH_APP2", Input::KI_LAUNCH_APP2)
	.value("OEM_AX", Input::KI_OEM_AX)
	.value("ICO_HELP", Input::KI_ICO_HELP)
	.value("ICO_00", Input::KI_ICO_00)
	.value("PROCESSKEY", Input::KI_PROCESSKEY)
	.value("ICO_CLEAR", Input::KI_ICO_CLEAR)
	.value("ATTN", Input::KI_ATTN)
	.value("CRSEL", Input::KI_CRSEL)
	.value("EXSEL", Input::KI_EXSEL)
	.value("EREOF", Input::KI_EREOF)
	.value("PLAY", Input::KI_PLAY)
	.value("ZOOM", Input::KI_ZOOM)
	.value("PA1", Input::KI_PA1)
	.value("OEM_CLEAR", Input::KI_OEM_CLEAR);

	sq_poptop(vm);
}











}
}
}
