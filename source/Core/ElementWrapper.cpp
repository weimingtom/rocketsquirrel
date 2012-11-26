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

#include "ElementWrapper.h"
#include "ElementInterface.h"
#include "VariantInterface.h"

#include <sqbind/SquirrelBind.h>
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"


namespace Rocket {
namespace Core {
namespace Squirrel {






ElementWrapper::ElementWrapper(const ElementWrapper& other)
{
	operator=(other);
}

ElementWrapper::ElementWrapper() : 
	m_pElement(0x0) 
{
}

ElementWrapper::~ElementWrapper()
{ 
	ROCKETSQUIRREL_ASSERT(m_pElement);
	m_pElement->RemoveReference();
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
	Rocket::Core::Element* elem = m_pElement->GetElementById(id);

	if (!elem)
	{
		//Returns itself
		elem = m_pElement;
	}

	ElementWrapper elemWrap;
	elemWrap.setElement(elem);

	return elemWrap;
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

void ElementWrapper::AppendChild(const ElementWrapper& element)
{
	m_pElement->AppendChild(element.m_pElement, false);
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

	ElementWrapper wrapper;

	wrapper.setElement(rocketElem);

	return wrapper;
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
}

ElementWrapper& ElementWrapper::operator= (const ElementWrapper& other)
{
	m_pElement = other.m_pElement;
	m_pElement->AddReference();

	return *this;
}

bool ElementWrapper::operator== (const ElementWrapper& other)
{
	return (m_pElement == other.m_pElement);
}

bool ElementWrapper::HasChildNodes() const
{
	return m_pElement->HasChildNodes();
}








}
}
}