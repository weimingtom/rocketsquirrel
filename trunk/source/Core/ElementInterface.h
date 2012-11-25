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

#ifndef __ROCKETSQUIRREL_ELEMENTINTERFACE_INCLUDED
#define __ROCKETSQUIRREL_ELEMENTINTERFACE_INCLUDED


#include <Rocket/Core/ElementDocument.h>
#include <squirrel.h>
#include <sqbind/SquirrelBind.h>


namespace Rocket {
namespace Core {
namespace Squirrel {



class ElementWrapper
{
protected:
	Rocket::Core::Element* m_pElement;

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

	void SetId(const char* id);
	const char* GetId() const;

	ElementWrapper& operator= (const ElementWrapper& other);

};


class ElementDocumentWrapper : public ElementWrapper
{
protected:

	Rocket::Core::ElementDocument* doc();

public:
	void Show(int flags);
	void Show();
	void Hide();
};


class ElementInterface
{
private:



public:

	ElementInterface();


	static SQInteger NoConstructable(HSQUIRRELVM vm);

	//Binding function
	static void Bind(HSQUIRRELVM vm);

	static void Register(HSQUIRRELVM vm);

	static void InitialiseRocketInterface();
};







}
}
}


SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::ElementWrapper);
SQBIND_DECLARE_CLASS(Rocket::Core::Squirrel::ElementDocumentWrapper);




#endif