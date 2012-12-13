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


#include "SquirrelScript.h"
#include "Debug.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






SquirrelScript::SquirrelScript(const Rocket::Core::String& code, const Rocket::Core::String& sourcename) :
	mCode(code),
	mSourceName(sourcename),
	mCompiled(false)
{
}

SquirrelScript::SquirrelScript() :
	mCompiled(false)
{
}

SQInteger SquirrelScript::WriteFunc(SQUserPointer script, SQUserPointer buffer, SQInteger size)
{
	SquirrelScript* pScript = (SquirrelScript*)script;

	for (SQInteger i = 0; i < size; i++)
	{
		pScript->mBytecode.push_back(((char*)buffer)[i]);
	}

	return size;
}

SQInteger SquirrelScript::ReadFunc(SQUserPointer script, SQUserPointer buffer, SQInteger size)
{
	SquirrelScript* pScript = (SquirrelScript*)script;

	SQInteger readCount = size;
	SQInteger readTotal = pScript->mReadIndex+readCount;
	SQInteger total = pScript->mBytecode.size();

	if (pScript->mReadIndex > total)
	{
		return -1;
	}

	if (readTotal > total)
	{
		readCount -= (readTotal - total);
	}

	for (SQInteger i = 0; i < readCount; i++)
	{
		((char*)buffer)[i] = pScript->mBytecode[pScript->mReadIndex+i];
	}

	pScript->mReadIndex += readCount;

	return readCount;
}

void SquirrelScript::Compile(HSQUIRRELVM vm, bool cacheBytecode)
{
	SQRESULT sqr;
	sqr = sq_compilebuffer(vm, mCode.CString(), mCode.Length(), mSourceName.CString(), true);

	mCacheBytecode = cacheBytecode;

	if (SQ_SUCCEEDED(sqr))
	{
		mCompiled = true;
		if (cacheBytecode)
		{
			//We clear the previous bytecode
			mBytecode.clear();
			if (SQ_FAILED(sq_writeclosure(vm, &WriteFunc, this)))
			{
				mCompiled = false;
				mCacheBytecode = false;
			}
		}
	}
}

bool SquirrelScript::IsCompiled() const
{
	return mCompiled;
}

void SquirrelScript::Run(HSQUIRRELVM vm)
{
	//sq_pushroottable(vm);

	if (mCacheBytecode)
	{
		if (mCompiled)
		{
			mReadIndex = 0;
			if (SQ_FAILED(sq_readclosure(vm, &ReadFunc, this)))
			{
				return;
			}

			//Push the function
			sq_push(vm, -2);
		}
	}
	else
	{
		mCompiled = false;
	}

	sq_call(vm, 1, false, true);


	//sq_poptop(vm);
}

void SquirrelScript::SetSourceCode(const Rocket::Core::String& code)
{
	mCode = code;
}

const Rocket::Core::String& SquirrelScript::GetSourceCode() const
{
	return mCode;
}

void SquirrelScript::SetSourceName(const Rocket::Core::String& name)
{
	mSourceName = name;
}

const Rocket::Core::String& SquirrelScript::GetSourceName() const
{
	return mSourceName;
}







}
}
}