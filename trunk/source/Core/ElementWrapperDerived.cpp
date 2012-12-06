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
#include "VariantInterface.h"
#include "ElementCaster.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"


namespace Rocket {
namespace Core {
namespace Squirrel {







void ElementDocumentWrapper::Show(int flags)
{
	doc()->Show(flags);
}

void ElementDocumentWrapper::Show()
{
	doc()->Show();
}

void ElementDocumentWrapper::Hide()
{
	doc()->Hide();
}

Rocket::Core::ElementDocument* ElementDocumentWrapper::doc()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);
	
	ROCKETSQUIRREL_ASSERT(dynamic_cast<Rocket::Core::ElementDocument*>(m_pElement));

	return (Rocket::Core::ElementDocument*)m_pElement;
}

void ElementDocumentWrapper::PullToFront()
{
	doc()->PullToFront();
}

void ElementDocumentWrapper::PushToBack()
{
	doc()->PushToBack();
}

void ElementDocumentWrapper::Close()
{
	doc()->Close();
}

ElementWrapper ElementDocumentWrapper::CreateElement(const char* name)
{
	Rocket::Core::Element* rocketElem = doc()->CreateElement(name);

	ROCKETSQUIRREL_ASSERT(rocketElem != 0x0);

	return __returnWrapper(rocketElem);
}

ElementTextWrapper ElementDocumentWrapper::CreateTextNode(const char* text)
{
	Rocket::Core::ElementText* rocketElem = doc()->CreateTextNode(text);

	ROCKETSQUIRREL_ASSERT(rocketElem != 0x0);

	ElementTextWrapper wrapper;

	//Why is giving a type error? it's a derived from Element isn't it?
	wrapper.setElement((Rocket::Core::Element*)rocketElem);

	return wrapper;


}

ContextInterface ElementDocumentWrapper::GetContext()
{
	ContextInterface context;
	//context.
	return context;
}

void ElementDocumentWrapper::SetTitle(const char* title)
{
	Rocket::Core::String strTitle(title);
	doc()->SetTitle(strTitle);
}

const char* ElementDocumentWrapper::GetTitle()
{
	return doc()->GetTitle().CString();
}

void ElementDocumentWrapper::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	/*Define the element document*/
	sqb::ClassDefinition<ElementDocumentWrapper, ElementWrapper> cEDoc(vm, -1, _SC("ElementDocument"));
	
	cEDoc.Constructor(&NoConstructable);
	cEDoc.ClassFunction(&ElementDocumentWrapper::PullToFront, _SC("PullToFront"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::PushToBack, _SC("PushToBack"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::Close, _SC("Close"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::CreateElement, _SC("CreateElement"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::CreateTextNode, _SC("CreateTextNode"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::GetTitle, _SC("GetTitle"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::SetTitle, _SC("SetTitle"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::GetContext, _SC("GetContext"));
	cEDoc.ClassFunction(&ElementDocumentWrapper::Hide, _SC("Hide"));
	cEDoc.ClassFunction<void (ElementDocumentWrapper::*)()>(&ElementDocumentWrapper::Show, _SC("Show"));
	cEDoc.ClassFunction<void (ElementDocumentWrapper::*)(int)>(&ElementDocumentWrapper::Show, _SC("ShowFocus"));
	
	cEDoc.EnumEntry(ElementDocument::NONE, "NONE");
	cEDoc.EnumEntry(ElementDocument::FOCUS, "FOCUS");
	cEDoc.EnumEntry(ElementDocument::MODAL, "MODAL");

	ElementCaster::SwitchTo(vm);

	bool r = sqb::Bind::BindNativeFunction(vm, -1, &ElementDocumentWrapper::Cast, _SC("Document"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC(".x")));

	sq_poptop(vm);
}

SQInteger ElementDocumentWrapper::Cast(HSQUIRRELVM vm)
{
	return ElementCaster::CastFunction<Rocket::Core::ElementDocument, ElementDocumentWrapper>(vm, "Document");
}


////////////////////////////////////////////////////////////////////

Rocket::Core::ElementText* ElementTextWrapper::text()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);
	ROCKETSQUIRREL_ASSERT(dynamic_cast<Rocket::Core::ElementText*>(m_pElement));
	return (Rocket::Core::ElementText*)m_pElement;
}

void ElementTextWrapper::SetText(const char* text)
{
	//TODO fix UTF8 convertion
	Rocket::Core::WString wstr(text);
	this->text()->SetText(wstr);
}

const char* ElementTextWrapper::GetText()
{
	//TODO fix UTF8 convertion
	text()->GetText().ToUTF8(mCacheText);
	return mCacheText.CString();
}

void ElementTextWrapper::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");


	/*Define the element text*/
	sqb::ClassDefinition<ElementTextWrapper, ElementWrapper> cEText(vm, -1, _SC("ElementText"));

	cEText.Constructor(&NoConstructable);
	cEText.ClassFunction(&ElementTextWrapper::SetText, _SC("SetText"));
	cEText.ClassFunction(&ElementTextWrapper::GetText, _SC("GetText"));

	ElementCaster::SwitchTo(vm);

	sqb::Bind::BindNativeFunction(vm, -1, &ElementTextWrapper::Cast, _SC("Text"), sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC(".x")));
	
	sq_poptop(vm);
}

SQInteger ElementTextWrapper::Cast(HSQUIRRELVM vm)
{
	return ElementCaster::CastFunction<Rocket::Core::ElementText, ElementTextWrapper>(vm, "Text");
}





}
}
}