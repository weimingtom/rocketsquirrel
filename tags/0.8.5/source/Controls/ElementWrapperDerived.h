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

#ifndef __ROCKETSQUIRREL_CONTROLS_ELEMENTWRAPPERDERIVED_INCLUDED
#define __ROCKETSQUIRREL_CONTROLS_ELEMENTWRAPPERDERIVED_INCLUDED


#include "../Core/ElementWrapper.h"
#include <Rocket/Controls/ElementForm.h>
#include <Rocket/Controls/ElementFormControl.h>
#include <Rocket/Controls/ElementFormControlInput.h>
#include <Rocket/Controls/ElementFormControlTextArea.h>
#include <Rocket/Controls/ElementFormControlSelect.h>



namespace Rocket {
namespace Controls {
namespace Squirrel {





/*! Wrapper for Rocket::Controls::ElementForm */
class ElementFormWrapper : public Rocket::Core::Squirrel::ElementWrapper
{
protected:
	Rocket::Controls::ElementForm* form();

public:

	SQInteger Submit(HSQUIRRELVM vm);

	static void Bind(HSQUIRRELVM vm);
	static SQInteger Cast(HSQUIRRELVM vm);
};





/*! Wrapper for Rocket::Controls::ElementFormControl */
class ElementFormControlWrapper : public Rocket::Core::Squirrel::ElementWrapper
{
protected:
	Rocket::Controls::ElementFormControl* formControl();

	//mutable Rocket::Core::String mValueCache;
	//mutable Rocket::Core::String mNameCache;

public:

	const char* GetName();
	void SetName(const char* name);

	const char* GetValue();
	void SetValue(const char* value);

	bool IsDisabled();
	void SetDisabled(bool disable);

	static void Bind(HSQUIRRELVM vm);
};

/*! Wrapper for Rocket::Controls::ElementFormControlInput */
class ElementFormControlInputWrapper : public ElementFormControlWrapper
{
protected:
	Rocket::Controls::ElementFormControlInput* formControlInput();

public:

	bool GetChecked();
	void SetChecked(bool checked);

	int GetMaxLength();
	void SetMaxLength(int max_length);

	int GetSize();
	void SetSize(int size);

	int GetMin();
	void SetMin(int min);
	int GetMax();
	void SetMax(int max);
	int GetStep();
	void SetStep(int step);

	static void Bind(HSQUIRRELVM vm);
	static SQInteger Cast(HSQUIRRELVM vm);
};

/*! Wrapper for Rocket::Controls::ElementFormControlTextArea */
class ElementFormControlTextAreaWrapper : public ElementFormControlWrapper
{
protected:
	Rocket::Controls::ElementFormControlTextArea* formControlTextArea();

public:


	int GetMaxLength();
	void SetMaxLength(int maxLength);

	void SetNumColumns(int numColumns);
	int GetNumColumns();

	void SetNumRows(int numRows);
	int GetNumRows();

	void SetWordWrap(bool wordWrap);
	bool GetWordWrap();

	static void Bind(HSQUIRRELVM vm);
	static SQInteger Cast(HSQUIRRELVM vm);
};

/*! Wrapper for Rocket::Controls::ElementFormControlSelect */
class ElementFormControlSelectWrapper : public ElementFormControlWrapper
{
protected:
	Rocket::Controls::ElementFormControlSelect* formControlSelect();

public:

	SQInteger Add(HSQUIRRELVM vm);
	void Remove(int index);
	void SetSelection(int selection);
	int GetSelection();

	static void Bind(HSQUIRRELVM vm);
	static SQInteger Cast(HSQUIRRELVM vm);
};

/*! Wrapper for Rocket::Controls::ElementFormControlDataSelect */
/*class ElementFormControlDataSelectWrapper : public ElementFormControlSelectWrapper
{
protected:
	Rocket::Controls::ElementFormControlSelect* formControlSelect();

public:

	SQInteger Add(HSQUIRRELVM vm);
	void Remove(int index);
	void SetSelection(int selection);
	int GetSelection();

	static void Bind(HSQUIRRELVM vm);
	static SQInteger Cast(HSQUIRRELVM vm);
};*/






}
}
}


SQBIND_DECLARE_CLASS(Rocket::Controls::Squirrel::ElementFormWrapper);
SQBIND_DECLARE_CLASS(Rocket::Controls::Squirrel::ElementFormControlWrapper);
SQBIND_DECLARE_CLASS(Rocket::Controls::Squirrel::ElementFormControlInputWrapper);
SQBIND_DECLARE_CLASS(Rocket::Controls::Squirrel::ElementFormControlTextAreaWrapper);
SQBIND_DECLARE_CLASS(Rocket::Controls::Squirrel::ElementFormControlSelectWrapper);



#endif