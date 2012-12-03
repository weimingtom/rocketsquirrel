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

#ifndef __ROCKETSQUIRREL_INTERFACES_INCLUDED
#define __ROCKETSQUIRREL_INTERFACES_INCLUDED


#include <Rocket/Core/URL.h>
#include <Rocket/Core/Log.h>
#include <Rocket/Core/Dictionary.h>
#include <Rocket/Core/Vector2.h>
#include <squirrel.h>
#include "VectorInterface.h"


namespace Rocket {
namespace Core {
namespace Squirrel {




void BindSquirrelInterfaces(HSQUIRRELVM vm);
void BindKeyMap(HSQUIRRELVM vm);





}
}
}


SQBIND_DECLARE_CLASS(Rocket::Core::String);

SQBIND_DECLARE_CLASS(Rocket::Core::StringList);

SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::VectorInterface<Rocket::Core::StringList>);

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2f);

SQBIND_DECLARE_CLASS(Rocket::Core::Vector2i);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourf);

SQBIND_DECLARE_CLASS(Rocket::Core::Colourb);

SQBIND_DECLARE_CLASS(Rocket::Core::URL);

SQBIND_DECLARE_CLASS(Rocket::Core::Log);

//SQBIND_DECLARE_ENUM(Rocket::Core::Log::Type);
SQBIND_DECLARE_CLASS(Rocket::Core::Log::Type);



#endif