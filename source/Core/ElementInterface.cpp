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

#include "ElementInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"
#include "ElementWrapper.h"
#include "ElementWrapperDerived.h"
#include "VariantInterface.h"
#include "VectorInterface.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






ElementInterface::ElementInterface()
{	
}

SQInteger ElementInterface::NoConstructable(HSQUIRRELVM vm)
{
	sqb::StackHandler sh(vm);
	return sh.ThrowError("This class cannot be instanced directly.");
}

void ElementInterface::Bind(HSQUIRRELVM vm)
{
	//ElementList
	sqb::ClassDefinition<VectorInterface<ElementWrapperList>> cVec(vm, -1, _SC("ElementList"));

	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::Contains, _SC("Contains"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::SetItem, _SC("_set"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::GetItem, _SC("_get"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::PushBack, _SC("append"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::PushBack, _SC("push"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::Size, _SC("len"));
	cVec.ClassFunction(&VectorInterface<ElementWrapperList>::DelItem, _SC("remove"));


	/*Define the base Element class*/
	sqb::ClassDefinition<ElementWrapper> cE(vm, -1, _SC("Element"));
	
	cE.Constructor(&ElementInterface::NoConstructable);

	cE.ClassFunction(&ElementWrapper::operator==, _SC("Equals"));
	cE.ClassFunction(&ElementWrapper::GetTagName, _SC("GetTagName"));
	cE.ClassFunction(&ElementWrapper::Blur, _SC("Blur"));
	cE.ClassFunction(&ElementWrapper::Click, _SC("Click"));
	cE.ClassFunction(&ElementWrapper::Focus, _SC("Focus"));
	cE.ClassFunction(&ElementWrapper::IsClassSet, _SC("IsClassSet"));
	cE.ClassFunction(&ElementWrapper::SetClass, _SC("SetClass"));
	cE.ClassFunction(&ElementWrapper::SetPseudoClass, _SC("SetPseudoClass"));
	cE.ClassFunction(&ElementWrapper::IsPseudoClassSet, _SC("IsPseudoClassSet"));
	cE.ClassFunction(&ElementWrapper::GetElementById, _SC("GetElementById"));
	cE.ClassFunction(&ElementWrapper::GetElementsByTagName, _SC("GetElementsByTagName"));
	cE.ClassFunction(&ElementWrapper::HasChildNodes, _SC("HasChildNodes"));
	cE.ClassFunction(&ElementWrapper::RemoveChild, _SC("RemoveChild"));
	cE.ClassFunction(&ElementWrapper::ReplaceChild, _SC("ReplaceChild"));
	cE.ClassFunction(&ElementWrapper::InsertBefore, _SC("InsertBefore"));
	cE.ClassFunction(&ElementWrapper::AppendChild, _SC("AppendChild"));
	cE.ClassFunction(&ElementWrapper::GetAddress, _SC("GetAddress"));
	cE.ClassFunction(&ElementWrapper::SetClassNames, _SC("SetClassNames"));
	cE.ClassFunction(&ElementWrapper::GetClassNames, _SC("GetClassNames"));
	cE.ClassFunction(&ElementWrapper::GetParentNode, _SC("GetParentNode"));
	cE.ClassFunction(&ElementWrapper::GetAttribute, _SC("GetAttribute"));
	cE.ClassFunction(&ElementWrapper::SetAttribute, _SC("SetAttribute"));
	cE.ClassFunction(&ElementWrapper::HasAttribute, _SC("HasAttribute"));
	cE.ClassFunction(&ElementWrapper::RemoveAttribute, _SC("RemoveAttribute"));
	cE.ClassFunction(&ElementWrapper::ScrollIntoView, _SC("ScrollIntoView"));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	cE.ClassFunction(&ElementWrapper::GetInnerRML, _SC("GetInnerRML"));
	cE.ClassFunction(&ElementWrapper::SetInnerRML, _SC("SetInnerRML"));
	cE.ClassFunction(&ElementWrapper::GetAbsoluteLeft, _SC("GetAbsoluteLeft"));
	cE.ClassFunction(&ElementWrapper::GetAbsoluteTop, _SC("GetAbsoluteTop"));
	cE.ClassFunction(&ElementWrapper::GetClientLeft, _SC("GetClientLeft"));
	cE.ClassFunction(&ElementWrapper::GetClientHeight, _SC("GetClientHeight"));
	cE.ClassFunction(&ElementWrapper::GetClientTop, _SC("GetClientTop"));
	cE.ClassFunction(&ElementWrapper::GetClientWidth, _SC("GetClientWidth"));
	cE.ClassFunction(&ElementWrapper::GetOffsetHeight, _SC("GetOffsetHeight"));
	cE.ClassFunction(&ElementWrapper::GetOffsetLeft, _SC("GetOffsetLeft"));
	cE.ClassFunction(&ElementWrapper::GetOffsetParent, _SC("GetOffsetParent"));
	cE.ClassFunction(&ElementWrapper::GetOffsetTop, _SC("GetOffsetTop"));
	cE.ClassFunction(&ElementWrapper::GetOffsetWidth, _SC("GetOffsetWidth"));
	cE.ClassFunction(&ElementWrapper::SetScrollLeft, _SC("SetScrollLeft"));
	cE.ClassFunction(&ElementWrapper::SetScrollTop, _SC("SetScrollTop"));
	cE.ClassFunction(&ElementWrapper::GetScrollLeft, _SC("GetScrollLeft"));
	cE.ClassFunction(&ElementWrapper::GetScrollTop, _SC("GetScrollTop"));
	cE.ClassFunction(&ElementWrapper::GetScrollWidth, _SC("GetScrollWidth"));
	cE.ClassFunction(&ElementWrapper::GetScrollHeight, _SC("GetScrollHeight"));
	cE.ClassFunction(&ElementWrapper::GetNextSibling, _SC("GetNextSibling"));
	cE.ClassFunction(&ElementWrapper::GetPreviousSibling, _SC("GetPreviousSibling"));
	cE.ClassFunction(&ElementWrapper::GetOwnerDocument, _SC("GetOwnerDocument"));
	cE.ClassFunction(&ElementWrapper::GetFirstChild, _SC("GetFirstChild"));
	cE.ClassFunction(&ElementWrapper::GetLastChild, _SC("GetLastChild"));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	//cE.ClassFunction(&ElementWrapper::, _SC(""));
	cE.ClassFunction(&ElementWrapper::GetId, _SC("GetId"));
	cE.ClassFunction(&ElementWrapper::SetId, _SC("SetId"));



	/*
	.def("AddEventListener", AddEventListener)
	.def("AddEventListener", AddEventListenerDefault)

	.def("DispatchEvent", &ElementInterface::DispatchEvent)
	.def("GetElementsByTagName", &ElementInterface::GetElementsByTagName)

	.add_property("attributes", &ElementInterface::GetAttributes)
	.add_property("child_nodes", &ElementInterface::GetChildren)
	.add_property("style", &ElementInterface::GetStyle)*/

	/*Define the element document*/
	sqb::ClassDefinition<ElementDocumentWrapper, ElementWrapper> cEDoc(vm, -1, _SC("ElementDocument"));
	
	cEDoc.Constructor(&ElementInterface::NoConstructable);
	cEDoc.ClassFunction(&ElementDocumentWrapper::Hide, _SC("Hide"));
	cEDoc.ClassFunction<void (ElementDocumentWrapper::*)()>(&ElementDocumentWrapper::Show, _SC("Show"));
	cEDoc.ClassFunction<void (ElementDocumentWrapper::*)(int)>(&ElementDocumentWrapper::Show, _SC("ShowFocus"));
	
	cEDoc.EnumEntry(ElementDocument::NONE, "NONE");
	cEDoc.EnumEntry(ElementDocument::FOCUS, "FOCUS");
	cEDoc.EnumEntry(ElementDocument::MODAL, "MODAL");
}

void ElementInterface::Register(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");

	Bind(vm);

	sq_poptop(vm);
}

void ElementInterface::InitialiseRocketInterface()
{

}












}
}
}