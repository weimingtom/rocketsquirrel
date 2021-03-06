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

#ifndef __ROCKETSQUIRREL_ELEMENTSTYLEPROXY_INCLUDED
#define __ROCKETSQUIRREL_ELEMENTSTYLEPROXY_INCLUDED


#include <Rocket/Core/Element.h>
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>
#include "VectorInterface.h"



namespace Rocket {
namespace Core {
namespace Squirrel {



class ElementStyleProxy
{
protected:
	Rocket::Core::String mCache;
	Rocket::Core::Element* m_pElement;

public:

	ElementStyleProxy(const ElementStyleProxy& other);
	ElementStyleProxy(Rocket::Core::Element* pElement);
	ElementStyleProxy();
	~ElementStyleProxy();

	void SetElement(Rocket::Core::Element* pElement);

	ElementStyleProxy& operator= (const ElementStyleProxy& other);

	SQInteger SetAttr(HSQUIRRELVM vm);

	SQInteger GetAttr(HSQUIRRELVM vm);

	static void Bind(HSQUIRRELVM vm);
};







}
}
}


SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::ElementStyleProxy);


#endif