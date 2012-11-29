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

#ifndef __ROCKETSQUIRREL_VECTORINTERFACE_INCLUDED
#define __ROCKETSQUIRREL_VECTORINTERFACE_INCLUDED


#include <Rocket/Core/Variant.h>
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include "../Debug.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






template <typename Container>
class VectorInterface
{
private:
	Container container;

public:

	Container& GetContainer()
	{
		return container;
	}

	VectorInterface()
	{
	}

	inline size_t Size()
	{
		return container.size();
	}

	inline void SetItem(int index, const typename Container::value_type& value)
	{
		if (index < 0)
			index = container.size() + index;
		if (index >= (int)container.size())
			container.resize(index + 1);

		container[index] = value;
	}

	inline void PushBack(const typename Container::value_type& value)
	{
		container.push_back(value);
	}

	inline void DelItem(int index)
	{
		if (index >= (int)container.size())
		{
			//Error here
			return; //TODO make native function
		}

		if (index < 0)
		{
			index = 0;
		}

		container.erase(container.begin() + index);
	}

	inline SQInteger GetItem(HSQUIRRELVM vm)
	{
		sqb::StackHandler sh(vm);

		ROCKETSQUIRREL_ASSERT(sh.GetParamCount() >= 2);
		ROCKETSQUIRREL_ASSERT(sh.IsNumber(2));

		SQInteger index = sh.GetInteger(2);

		if (index < 0)
			index = container.size() + index;

		if (index >= (int)container.size())
		{
			//error here
			return sh.ThrowNull();
		}

		return sh.Return<typename Container::value_type>(container[index]);
	}

	inline bool Contains(const typename Container::value_type& value)
	{
		for (typename Container::iterator itr = container.begin(); itr != container.end(); ++itr)
		{
			if ((*itr) == value)
				return true;
		}

		return false;
	}
};








}
}
}







#endif