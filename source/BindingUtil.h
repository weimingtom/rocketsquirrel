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

#ifndef __ROCKETSQUIRREL_BINDINGUTIL_INCLUDED
#define __ROCKETSQUIRREL_BINDINGUTIL_INCLUDED



#include <squirrel.h>
#include <Rocket/Core/Debug.h>


namespace Rocket {
	namespace Squirrel {





		void squirrelPrintFunc(HSQUIRRELVM v,const SQChar *s,...);
		void squirrelCompileErrorFunc(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column);

		SQRESULT compileNutFile(HSQUIRRELVM v, const char *filename);

		
		SQInteger squirrelPrintRuntimeError(HSQUIRRELVM v);
		void squirrelPrintCallStack(HSQUIRRELVM v);



		template <typename T>
		inline T* squirrelGetInstanceObj(HSQUIRRELVM v)
		{
			SQUserPointer p = NULL;

			ROCKET_ASSERT(sq_gettype(v, 1) == OT_INSTANCE);

			//TODO make this a little bit more safe
			SQRESULT sqr = sq_getinstanceup(v, 1, &p, 0);

			ROCKET_ASSERT(SQ_SUCCEDED(sqr)); 

			return (T*)p;
		}



	}
}






#endif