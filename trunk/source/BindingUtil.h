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
#include <sqbind/sqbStackHandler.h>


namespace Rocket {
namespace Core {
namespace Squirrel {





void PrintFunc(HSQUIRRELVM v,const SQChar *s,...);
void CompileErrorFunc(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column);

SQRESULT CompileNutFile(HSQUIRRELVM v, const char *filename);

		
SQInteger PrintRuntimeError(HSQUIRRELVM v);
void PrintCallStack(HSQUIRRELVM v);


/*!
 * Utility class to compare classes tag ids to filter out types 
 * from the stack
 *
 *	//Gets the tag id from the stack at index 1
 *	TypeTagUtility tagutil(vm, 1);
 *
 *	//You can also switch the index by caling
 *	tagutil.getTypeTagAt(2);
 *
 *	//Then you can compare it
 *	if (tagutil.matches<MyNameSpace::MyClass>())
 *	{
 *	//Get the instance and do something with it
 * 	}
 *
 */
class TypeTagUtility 
{
protected:
	HSQUIRRELVM mVM;
	SQUserPointer mTypeTagID;

public:
	/*!
	 * Initializes the object with the selected VM
	 * and gets the TagID from the stack at index $idx
	 */
	TypeTagUtility(HSQUIRRELVM vm, SQInteger idx = 1);
	
	/*!
	 * Gets the typetag id from the stack at index $idx.
	 * You can call this as many times you want
	 * as long the idx is not the same ovbiously
	 */
	void getTypeTagAt(SQInteger idx);

	/*!
	 * Returns true if the type is equal to the TypeTag
	 */
	template <typename T>
	inline bool matches()
	{
		//Get the tag
		sqb::ClassTypeTag<T>* classTypeTag = sqb::ClassTypeTag<T>::Get();

		//Compare the tag id in the stack with the one provided
		return (mTypeTagID == classTypeTag);
	}


};

/*!
 * Gets the UsrPointer from the stack at index idx
 */
SQUserPointer GetInstance(HSQUIRRELVM vm, SQInteger idx = 1);

template <typename T>
inline T* NewInstance(HSQUIRRELVM vm)
{
	sqb::StackHandler stack(vm);

	sqb::ClassTypeTag<T>* classTypeTag = sqb::ClassTypeTag<T>::Get();

	SQUserPointer userPointer = GetInstance(vm);

	SQRELEASEHOOK hook = classTypeTag->GetReleaseHook();
	sq_setreleasehook(vm, 1, hook);

	T* instance = new (userPointer)T();
	(void)instance;

	return (T*)instance;
}







}
}
}






#endif