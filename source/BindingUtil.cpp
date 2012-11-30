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

#include "BindingUtil.h"

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Debug.h"

#include "RocketSquirrel.h"
#include "RocketSquirrel/Core/ScriptInterface.h"

#ifdef _WINDOWS
#include <Windows.h>
#endif


namespace Rocket {
namespace Core {
namespace Squirrel {





static char buffer[1024];


void PrintErrorFunc(HSQUIRRELVM v,const SQChar *s,...)
{
	va_list vl;
	va_start(vl, s);

	vsnprintf(buffer, 1024, s, vl);

	va_end(vl);
	
	Module::instance().getScriptInterface().Print(buffer);
}

void PrintFunc(HSQUIRRELVM v,const SQChar *s,...)
{
	
	va_list vl;
	va_start(vl, s);

	vsnprintf(buffer, 1024, s, vl);

	va_end(vl);
	
	Module::instance().getScriptInterface().Print(buffer);
}


void CompileErrorFunc(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
{
	std::cout << "Source: " << source << " Line: " << line << std::endl;
	std::cout << std::endl << desc << std::endl;

	Module::instance().getScriptInterface().ReportCompilationError(desc, source, line, column);

#ifdef _WINDOWS
	OutputDebugString(desc);
#endif
}


static SQInteger file_lexfeedASCII(SQUserPointer file)
{
	int ret;
	char c;
	if( ( ret=fread(&c,sizeof(c),1,(FILE *)file )>0) )
		return c;
	return 0;
}

SQRESULT CompileNutFile(HSQUIRRELVM v, const char *filename)
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


SQInteger NoConstructable(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);
	return sh.ThrowError("This class cannot be instanced directly.");
}


void PrintCallStack(HSQUIRRELVM v)
{
	SQPRINTFUNCTION pf = sq_geterrorfunc(v);
	if(pf) {
		SQStackInfos si;
		SQInteger i;
		SQFloat f;
		const SQChar *s;
		SQInteger level=1; //1 is to skip this function that is level 0
		const SQChar *name=0; 
		SQInteger seq=0;
		pf(v,_SC("\nCALLSTACK\n"));
		while(SQ_SUCCEEDED(sq_stackinfos(v,level,&si)))
		{
			const SQChar *fn=_SC("unknown");
			const SQChar *src=_SC("unknown");
			if(si.funcname)fn=si.funcname;
			if(si.source)src=si.source;
			pf(v,_SC("*FUNCTION [%s()] %s line [%d]\n"),fn,src,si.line);
			level++;
		}

		return;
		level=0;
		pf(v,_SC("\nLOCALS\n"));

		for(level=0;level<10;level++){
			seq=0;
			while((name = sq_getlocal(v,level,seq)))
			{
				seq++;
				switch(sq_gettype(v,-1))
				{
				case OT_NULL:
					pf(v,_SC("[%s] NULL\n"),name);
					break;
				case OT_INTEGER:
					sq_getinteger(v,-1,&i);
					pf(v,_SC("[%s] %d\n"),name,i);
					break;
				case OT_FLOAT:
					sq_getfloat(v,-1,&f);
					pf(v,_SC("[%s] %.14g\n"),name,f);
					break;
				case OT_USERPOINTER:
					pf(v,_SC("[%s] USERPOINTER\n"),name);
					break;
				case OT_STRING:
					sq_getstring(v,-1,&s);
					pf(v,_SC("[%s] \"%s\"\n"),name,s);
					break;
				case OT_TABLE:
					pf(v,_SC("[%s] TABLE\n"),name);
					break;
				case OT_ARRAY:
					pf(v,_SC("[%s] ARRAY\n"),name);
					break;
				case OT_CLOSURE:
					pf(v,_SC("[%s] CLOSURE\n"),name);
					break;
				case OT_NATIVECLOSURE:
					pf(v,_SC("[%s] NATIVECLOSURE\n"),name);
					break;
				case OT_GENERATOR:
					pf(v,_SC("[%s] GENERATOR\n"),name);
					break;
				case OT_USERDATA:
					pf(v,_SC("[%s] USERDATA\n"),name);
					break;
				case OT_THREAD:
					pf(v,_SC("[%s] THREAD\n"),name);
					break;
				case OT_CLASS:
					pf(v,_SC("[%s] CLASS\n"),name);
					break;
				case OT_INSTANCE:
					pf(v,_SC("[%s] INSTANCE\n"),name);
					break;
				case OT_WEAKREF:
					pf(v,_SC("[%s] WEAKREF\n"),name);
					break;
				case OT_BOOL:{
					sq_getinteger(v,-1,&i);
					pf(v,_SC("[%s] %s\n"),name,i?_SC("true"):_SC("false"));
								}
					break;
				default: ROCKETSQUIRREL_ASSERT(0); break;
				}
				sq_pop(v,1);
			}
		}
	}
}

SQInteger PrintRuntimeError(HSQUIRRELVM v)
{
	SQPRINTFUNCTION pf = sq_geterrorfunc(v);
	if(pf) {
		const SQChar *sErr = 0;
		if(sq_gettop(v)>=1) {
			if(SQ_SUCCEEDED(sq_getstring(v,2,&sErr)))	{
				pf(v,_SC("\nAN ERROR HAS OCCURED [%s]\n"),sErr);
			}
			else{
				pf(v,_SC("\nAN ERROR HAS OCCURED [unknown]\n"));
			}
			PrintCallStack(v);
		}
	}

	return 0;
}


SQUserPointer GetInstance(HSQUIRRELVM vm, SQInteger idx)
{
	sqb::StackHandler stack(vm);

	SQUserPointer userPointer;
	ROCKETSQUIRREL_ASSERT(sq_gettype(vm, idx) == OT_INSTANCE);

	sq_getinstanceup(vm, idx, &userPointer, nullptr);
	ROCKETSQUIRREL_ASSERT(userPointer != nullptr);
			
	return userPointer;
}



TypeTagUtility::TypeTagUtility(HSQUIRRELVM vm, SQInteger idx) :
	mVM(vm)
{
	getTypeTagAt(idx);
}
	
void TypeTagUtility::getTypeTagAt(SQInteger idx)
{
	SQRESULT sqr = sq_gettypetag(mVM, 2, &mTypeTagID);

	ROCKETSQUIRREL_ASSERT(SQ_SUCCEEDED(sqr));
}





}
}
}
