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

#ifndef __ROCKETSQUIRREL_ELEMENTWRAPPER_INCLUDED
#define __ROCKETSQUIRREL_ELEMENTWRAPPER_INCLUDED


#include <Rocket/Core/Element.h>
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>


namespace Rocket {
namespace Core {
namespace Squirrel {





class ElementWrapper
{
protected:
	Rocket::Core::Element* m_pElement;

	mutable Rocket::Core::String mCacheAddress;
	mutable Rocket::Core::String mCacheClassNames;

public:

	ElementWrapper(const ElementWrapper& other);
	ElementWrapper();
	virtual ~ElementWrapper();

	void setElement(Rocket::Core::Element* pElement);
	Rocket::Core::Element* getElement();

	const char* GetTagName() const;

	void Blur();
	void Click();
	bool Focus();
	bool IsClassSet(const char* classname) const;
	void SetClass(const char* classname, bool activate);
	void SetPseudoClass(const char* classname, bool activate);
	bool IsPseudoClassSet(const char* classname) const;
	const char* GetClassNames() const;
	void SetClassNames(const char* classnames);

	const char* GetAddress(bool include_pseudo_classes) const;

	bool HasChildNodes() const;
	bool RemoveChild(const ElementWrapper& element);
	bool ReplaceChild(const ElementWrapper& element, const ElementWrapper& replacement);
	void InsertBefore(const ElementWrapper& element, const ElementWrapper& adjacentelement);
	void AppendChild(const ElementWrapper& element);

	float GetAbsoluteLeft() const;
	float GetAbsoluteTop() const;

	float GetClientLeft() const;
	float GetClientTop() const;
	float GetClientWidth() const;
	float GetClientHeight() const;

	ElementWrapper GetOffsetParent() const;
	float GetOffsetLeft() const;
	float GetOffsetTop() const;
	float GetOffsetWidth() const;
	float GetOffsetHeight() const;

	void SetId(const char* id);
	const char* GetId() const;

	ElementWrapper GetElementById(const char* id) const;

	ElementWrapper& operator= (const ElementWrapper& other);

	bool operator== (const ElementWrapper& other);
};







}
}
}


SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::ElementWrapper);



#endif