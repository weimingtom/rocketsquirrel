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

#include "ElementWrapper.h"
#include "ElementInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"

#include "ElementWrapperDerived.h"
#include "ElementStyleProxy.h"
#include <Rocket/Core/Factory.h>
#include "EventListener.h"
#include "DictionaryInterface.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






ElementWrapper::ElementWrapper(const ElementWrapper& other) :
	m_pElement(0x0)
{
	operator=(other);
}

ElementWrapper::ElementWrapper() : 
	m_pElement(0x0) 
{
}

ElementWrapper::~ElementWrapper()
{ 
	//ROCKETSQUIRREL_ASSERT(m_pElement);
	if (m_pElement)
	{	
		m_pElement->RemoveReference();
	}
}

const char* ElementWrapper::GetTagName() const
{
	return m_pElement->GetTagName().CString();
}

void ElementWrapper::Blur()
{
	m_pElement->Blur();
}

void ElementWrapper::Click()
{
	m_pElement->Click();
}

bool ElementWrapper::Focus()
{
	return m_pElement->Focus();
}

void ElementWrapper::SetClass(const char* classname, bool activate)
{
	m_pElement->SetClass(classname, activate);
}

bool ElementWrapper::IsClassSet(const char* classname) const
{
	return m_pElement->IsClassSet(classname);
}

void ElementWrapper::SetPseudoClass(const char* classname, bool activate)
{
	m_pElement->SetPseudoClass(classname, activate);
}

bool ElementWrapper::IsPseudoClassSet(const char* classname) const
{
	return m_pElement->IsPseudoClassSet(classname);
}

void ElementWrapper::SetId(const char* id)
{
	m_pElement->SetId(id);
}

const char* ElementWrapper::GetId() const
{
	return m_pElement->GetId().CString();
}

ElementWrapper ElementWrapper::GetElementById(const char* id) const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetElementById(id);
	return __returnWrapper(rocketElem);
}

VectorInterface<ElementWrapperList> ElementWrapper::GetElementsByTagName(const char* tag) const
{
	Rocket::Core::ElementList rocketList;
	m_pElement->GetElementsByTagName(rocketList, tag);


	VectorInterface<ElementWrapperList> vector;

	ElementWrapperList& list = vector.GetContainer();

	list.resize(rocketList.size());

	for (size_t i = 0; i < list.size(); i++)
	{
		list[i].setElement(rocketList[i]);
	}

	return vector;
}

bool ElementWrapper::RemoveChild(const ElementWrapper& element)
{
	return m_pElement->RemoveChild(element.m_pElement);
}

bool ElementWrapper::ReplaceChild(const ElementWrapper& element, const ElementWrapper& replacement)
{
	return m_pElement->ReplaceChild(element.m_pElement, replacement.m_pElement);
}

void ElementWrapper::InsertBefore(const ElementWrapper& element, const ElementWrapper& adjacentelement)
{
	m_pElement->InsertBefore(element.m_pElement, adjacentelement.m_pElement);
}

ElementWrapper ElementWrapper::GetFirstChild() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetFirstChild();
	return __returnWrapper(rocketElem);
}

ElementWrapper ElementWrapper::GetLastChild() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetLastChild();
	return __returnWrapper(rocketElem);
}

void ElementWrapper::AppendChild(const ElementWrapper& element)
{
	m_pElement->AppendChild(element.m_pElement);
}

float ElementWrapper::GetAbsoluteLeft() const
{
	return m_pElement->GetAbsoluteLeft();
}

float ElementWrapper::GetAbsoluteTop() const
{
	return m_pElement->GetAbsoluteTop();
}

const char* ElementWrapper::GetAddress(bool include_pseudo_classes) const
{
	mCacheAddress = m_pElement->GetAddress(include_pseudo_classes);
	return mCacheAddress.CString();
}

const char* ElementWrapper::GetClassNames() const
{
	mCacheClassNames = m_pElement->GetClassNames();
	return mCacheClassNames.CString();
}

void ElementWrapper::SetClassNames(const char* classnames)
{
	m_pElement->SetClassNames(classnames);
}

float ElementWrapper::GetClientLeft() const
{
	return m_pElement->GetClientLeft();
}

float ElementWrapper::GetClientTop() const
{
	return m_pElement->GetClientTop();
}

float ElementWrapper::GetClientWidth() const
{
	return m_pElement->GetClientWidth();
}

float ElementWrapper::GetClientHeight() const
{
	return m_pElement->GetClientHeight();
}

ElementWrapper ElementWrapper::GetOffsetParent() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetOffsetParent();
	ROCKETSQUIRREL_ASSERT(rocketElem != 0x0);
	return __returnWrapper(rocketElem);
}

float ElementWrapper::GetOffsetLeft() const
{
	return m_pElement->GetOffsetLeft();
}

float ElementWrapper::GetOffsetTop() const
{
	return m_pElement->GetOffsetTop();
}

float ElementWrapper::GetOffsetWidth() const
{
	return m_pElement->GetOffsetWidth();
}

float ElementWrapper::GetOffsetHeight() const
{
	return m_pElement->GetOffsetHeight();
}

void ElementWrapper::SetScrollLeft(float val)
{
	m_pElement->SetScrollLeft(val);
}

void ElementWrapper::SetScrollTop(float val)
{
	m_pElement->SetScrollTop(val);
}

float ElementWrapper::GetScrollLeft() const
{
	return m_pElement->GetScrollLeft();
}

float ElementWrapper::GetScrollTop() const
{
	return m_pElement->GetScrollTop();
}

float ElementWrapper::GetScrollWidth() const
{
	return m_pElement->GetScrollWidth();
}

float ElementWrapper::GetScrollHeight() const
{
	return m_pElement->GetScrollHeight();
}

ElementWrapper ElementWrapper::GetParentNode() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetParentNode();
	return __returnWrapper(rocketElem);
}

Rocket::Core::Element* ElementWrapper::getElement()
{
	ROCKETSQUIRREL_ASSERT(m_pElement);
	return m_pElement;
}

void ElementWrapper::setElement(Rocket::Core::Element* pElement)
{
	//This wrapper should be virgin before attemping to set the element pointer
	ROCKETSQUIRREL_ASSERT(m_pElement == 0x0);
	m_pElement = pElement;
	m_pElement->AddReference();
	style.SetElement(m_pElement);
}

ElementWrapper& ElementWrapper::operator= (const ElementWrapper& other)
{
	if (other.m_pElement == 0x0)
	{
		return *this;
	}

	ROCKETSQUIRREL_ASSERT(m_pElement == 0x0);

	m_pElement = other.m_pElement;
	m_pElement->AddReference();
	style.SetElement(m_pElement);

	return *this;
}

bool ElementWrapper::operator== (const ElementWrapper& other) const
{
	return (m_pElement == other.m_pElement);
}

bool ElementWrapper::HasChildNodes() const
{
	return m_pElement->HasChildNodes();
}

ElementDocumentWrapper ElementWrapper::GetOwnerDocument()
{
	Rocket::Core::ElementDocument* rocketDoc = m_pElement->GetOwnerDocument();

	ROCKETSQUIRREL_ASSERT(rocketDoc != 0x0);

	ElementDocumentWrapper wrapper;
	wrapper.setElement(rocketDoc);

	return wrapper;
}

ElementWrapper ElementWrapper::GetNextSibling() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetNextSibling();
	return __returnWrapper(rocketElem);
}

ElementWrapper ElementWrapper::GetPreviousSibling() const
{
	Rocket::Core::Element* rocketElem = m_pElement->GetPreviousSibling();
	return __returnWrapper(rocketElem);
}

ElementWrapper ElementWrapper::__returnWrapper(Rocket::Core::Element* element) const
{
	if (!element)
	{
		element = m_pElement;
	}

	ElementWrapper wrapper;

	wrapper.setElement(element);

	return wrapper;
}

void ElementWrapper::SetAttribute(const char* name, const VariantInterface& value)
{
	m_pElement->SetAttribute<Rocket::Core::Variant>(name, value);
}

VariantInterface ElementWrapper::GetAttribute(const char* name) const
{
	Rocket::Core::Variant* attr = m_pElement->GetAttribute(name);

	if (attr)
	{
		return VariantInterface(*attr);
	}

	//Null
	return VariantInterface();
}

bool ElementWrapper::HasAttribute(const char* name)
{
	return m_pElement->HasAttribute(name);
}

void ElementWrapper::RemoveAttribute(const char* name)
{
	m_pElement->RemoveAttribute(name);
}

void ElementWrapper::ScrollIntoView(bool alingtop)
{
	m_pElement->ScrollIntoView(alingtop);
}

const char* ElementWrapper::GetInnerRML() const
{
	mCacheInnerRML.Clear();
	m_pElement->GetInnerRML(mCacheInnerRML);

	return mCacheInnerRML.CString();
}

void ElementWrapper::SetInnerRML(const char* rml)
{
	m_pElement->SetInnerRML(rml);
}

ElementWrapperList ElementWrapper::GetChildren() const
{
	//TODO where is it?
	return ElementWrapperList();
}

void ElementWrapper::AddEventListener(const char* evt, const char* code, bool inCapturePhase)
{
	Rocket::Core::EventListener* listener = Rocket::Core::Factory::InstanceEventListener(code);

	m_pElement->AddEventListener(evt, listener, inCapturePhase);
}

void ElementWrapper::DispatchEvent(const char* evt, DictionaryInterface& dict, bool interruptible)
{
	m_pElement->DispatchEvent(evt, dict.GetRocketDictionary(), interruptible);
}

void ElementWrapper::Bind(HSQUIRRELVM vm)
{
	/*Define the base Element class*/
	sqb::ClassDefinition<ElementWrapper> cE(vm, -1, _SC("Element"));
	
	cE.Constructor(&NoConstructable);

	cE.Variable(&ElementWrapper::style, _SC("style"));
	cE.ClassFunction(&ElementWrapper::AddEventListener, _SC("AddEventListener"));
	cE.ClassFunction(&ElementWrapper::DispatchEvent, _SC("DispatchEvent"));
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
	cE.ClassFunction(&ElementWrapper::GetId, _SC("GetId"));
	cE.ClassFunction(&ElementWrapper::SetId, _SC("SetId"));
}








}
}
}