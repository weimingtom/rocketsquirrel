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

#include "ElementWrapperDerived.h"
#include "ElementInterface.h"
#include "../Core/ElementCaster.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"


namespace Rocket {
namespace Controls {
namespace Squirrel {


using Rocket::Core::Squirrel::NamespaceHelper;
using Rocket::Core::Squirrel::NoConstructable;
using Rocket::Core::Squirrel::ElementCaster;




Rocket::Controls::ElementForm* ElementFormWrapper::form()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);

	ROCKETSQUIRREL_ASSERT(dynamic_cast<Rocket::Controls::ElementForm*>(m_pElement));

	return (Rocket::Controls::ElementForm*)m_pElement;
}

SQInteger ElementFormWrapper::Submit(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);

	int paramCount = sh.GetParamCount();
	ROCKETSQUIRREL_ASSERT(paramCount >= 1);

	Rocket::Core::String name, value;

	if (paramCount >= 2)
	{
		if (sh.IsString(2))
		{
			name = sh.GetString(2);
		}
	}

	if (paramCount >= 3)
	{
		if (sh.IsString(3))
		{
			value = sh.GetString(3);
		}
	}

	form()->Submit(name, value);

	return sh.Return();
}

void ElementFormWrapper::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	sqb::ClassDefinition<ElementFormWrapper, ElementWrapper> cEForm(vm, -1, _SC("ElementForm"));
	
	cEForm.Constructor(&NoConstructable);
	cEForm.NativeClassFunction(&ElementFormWrapper::Submit, _SC("Submit"), sqb::FunctionOptions().ParamCheckCount(-1).TypeMask(_SC("xss")));

	ElementCaster::SwitchTo(vm);

	bool r = sqb::Bind::BindNativeFunction(vm, -1, &ElementFormWrapper::Cast, _SC("Form"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC(".x")));

	sq_poptop(vm);
}

SQInteger ElementFormWrapper::Cast(HSQUIRRELVM vm)
{
	return ElementCaster::CastFunction<Rocket::Controls::ElementForm, ElementFormWrapper>(vm, "Form");
}



/////////////////////////////////////////////////////////////////////



Rocket::Controls::ElementFormControl* ElementFormControlWrapper::formControl()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);

	ROCKETSQUIRREL_ASSERT(dynamic_cast<Rocket::Controls::ElementFormControl*>(m_pElement));

	return (Rocket::Controls::ElementFormControl*)m_pElement;
}

const char* ElementFormControlWrapper::GetName()
{
	return formControl()->GetName().CString();
}

void ElementFormControlWrapper::SetName(const char* name)
{
	formControl()->SetName(name);
}

const char* ElementFormControlWrapper::GetValue()
{
	return formControl()->GetValue().CString();
}

void ElementFormControlWrapper::SetValue(const char* value)
{
	formControl()->SetValue(value);
}

bool ElementFormControlWrapper::IsDisabled()
{
	return formControl()->IsDisabled();
}

void ElementFormControlWrapper::SetDisabled(bool disable)
{
	formControl()->SetDisabled(disable);
}

void ElementFormControlWrapper::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	sqb::ClassDefinition<ElementFormControlWrapper, ElementWrapper> cEFormControl(vm, -1, _SC("ElementFormControl"));
	
	cEFormControl.Constructor(&NoConstructable);
	cEFormControl.ClassFunction(&ElementFormControlWrapper::GetName, _SC("GetName"));
	cEFormControl.ClassFunction(&ElementFormControlWrapper::SetName, _SC("SetName"));
	cEFormControl.ClassFunction(&ElementFormControlWrapper::GetValue, _SC("GetValue"));
	cEFormControl.ClassFunction(&ElementFormControlWrapper::SetValue, _SC("SetValue"));
	cEFormControl.ClassFunction(&ElementFormControlWrapper::IsDisabled, _SC("IsDisabled"));
	cEFormControl.ClassFunction(&ElementFormControlWrapper::SetDisabled, _SC("SetDisabled"));

	sq_poptop(vm);
}


/////////////////////////////////////////////////////////


Rocket::Controls::ElementFormControlInput* ElementFormControlInputWrapper::formControlInput()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);

	ROCKETSQUIRREL_ASSERT(dynamic_cast<Rocket::Controls::ElementFormControlInput*>(m_pElement));

	return (Rocket::Controls::ElementFormControlInput*)m_pElement;
}

bool ElementFormControlInputWrapper::GetChecked()
{
	return m_pElement->HasAttribute("checked");
}

void ElementFormControlInputWrapper::SetChecked(bool checked)
{
	if (checked)
	{
		m_pElement->SetAttribute("checked", true);
	}
	else
	{
		m_pElement->RemoveAttribute("checked");
	}
}

int ElementFormControlInputWrapper::GetMaxLength()
{
	return m_pElement->GetAttribute<int>("maxlength", -1);
}

void ElementFormControlInputWrapper::SetMaxLength(int max_length)
{
	m_pElement->SetAttribute("maxlength", max_length);
}

int ElementFormControlInputWrapper::GetSize()
{
	return m_pElement->GetAttribute<int>("size", 20);
}

void ElementFormControlInputWrapper::SetSize(int size)
{
	m_pElement->SetAttribute("size", size);
}

int ElementFormControlInputWrapper::GetMin()
{
	return m_pElement->GetAttribute<int>("min", 0);
}

void ElementFormControlInputWrapper::SetMin(int min)
{
	m_pElement->SetAttribute("min", min);
}

int ElementFormControlInputWrapper::GetMax()
{
	return m_pElement->GetAttribute<int>("max", 100);
}

void ElementFormControlInputWrapper::SetMax(int max)
{
	m_pElement->SetAttribute("max", max);
}

int ElementFormControlInputWrapper::GetStep()
{
	return m_pElement->GetAttribute<int>("step", 1);
}

void ElementFormControlInputWrapper::SetStep(int step)
{
	m_pElement->SetAttribute("step", step);
}

void ElementFormControlInputWrapper::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	sqb::ClassDefinition<ElementFormControlInputWrapper, ElementFormControlWrapper> cEInput(vm, -1, _SC("ElementFormControlInput"));
	
	cEInput.Constructor(&NoConstructable);
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetChecked, _SC("SetChecked"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetChecked, _SC("GetChecked"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetMaxLength, _SC("SetMaxLength"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetMaxLength, _SC("GetMaxLength"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetSize, _SC("SetSize"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetSize, _SC("GetSize"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetMax, _SC("SetMax"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetMax, _SC("GetMax"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetMin, _SC("SetMin"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetMin, _SC("GetMin"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::SetStep, _SC("SetStep"));
	cEInput.ClassFunction(&ElementFormControlInputWrapper::GetStep, _SC("GetStep"));

	ElementCaster::SwitchTo(vm);

	bool r = sqb::Bind::BindNativeFunction(vm, -1, &ElementFormControlInputWrapper::Cast, _SC("Input"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC(".x")));

	sq_poptop(vm);
}

SQInteger ElementFormControlInputWrapper::Cast(HSQUIRRELVM vm)
{
	return ElementCaster::CastFunction<Rocket::Controls::ElementFormControlInput, ElementFormControlInputWrapper>(vm, "Input");
}





}
}
}