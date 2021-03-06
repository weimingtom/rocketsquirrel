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

#ifndef __ROCKETSQUIRREL_ELEMENTCASTER_INCLUDED
#define __ROCKETSQUIRREL_ELEMENTCASTER_INCLUDED


#include <Rocket/Core/Element.h>
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include "ElementWrapper.h"
#include <map>



namespace Rocket {
namespace Core {
namespace Squirrel {


class ElementDocumentWrapper;
class ElementWrapper;



typedef std::vector<ElementWrapper> ElementWrapperList;



class ElementCaster
{
protected:

public:

	static void Bind(HSQUIRRELVM vm);
	static SQInteger ThrowErrorUnknown(HSQUIRRELVM vm);
	static SQInteger ThrowErrorNotElement(HSQUIRRELVM vm);
	static SQInteger ThrowErrorCastFailed(HSQUIRRELVM vm, const char* targetClass);

	static void SwitchTo(HSQUIRRELVM vm);

	/*! T stands for type W for wrapper */
	template<typename T, typename W>
	inline static SQInteger CastFunction(HSQUIRRELVM vm, const char* name)
	{
		sqb::StackHandler sh(vm);

		ROCKETSQUIRREL_ASSERT(sh.GetParamCount() >= 2);
		ROCKETSQUIRREL_ASSERT(sh.IsInstance(2));

		if (!sh.IsInstanceOfType<ElementWrapper>(2))
		{
			return ElementCaster::ThrowErrorNotElement(vm);
		}

		T* obj = dynamic_cast<T*>(sh.GetInstanceAsType<ElementWrapper>(2)->getElement());

		if (obj)
		{
			W wrapper;
			wrapper.setElement(obj);
			return sqb::Push<W>(vm, wrapper);
		}
		else
		{
			return ElementCaster::ThrowErrorCastFailed(vm, name);
		}

		return ElementCaster::ThrowErrorUnknown(vm);
	}
};







}
}
}



#endif
