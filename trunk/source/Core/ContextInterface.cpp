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

#include "ContextInterface.h"

#include <Rocket/Core/Context.h>
#include <Rocket/Core/Factory.h>
#include <Rocket/Core.h>
#include <Rocket/Core/Vector2.h>

#include "ContextInstancer.h"
#include "../Debug.h"
#include "../BindingUtil.h"
#include "../NamespaceHelper.h"
#include "Interfaces.h"
#include "ElementInterface.h"
#include "ElementWrapperDerived.h"
#include <Rocket/Debugger.h>



namespace Rocket {
namespace Core {
namespace Squirrel {






ContextInterface::ContextInterface()
{
}

ContextInterface::~ContextInterface()
{
	//m_pContext->RemoveReference();
}

SQInteger ContextInterface::constructor(HSQUIRRELVM v)
{
	sqb::StackHandler sh(v);

	Rocket::Core::String name;
	Rocket::Core::Vector2i dim(800, 600);

	SQInteger args = sh.GetParamCount();

	if (args >= 2)
	{
		if (sh.IsString(2))
		{
			name = sh.GetString(2);
		}

		if (args >= 3)
		{
			if (sh.IsInstance(3) && sh.IsInstanceOfType<Rocket::Core::Vector2i>(3))
			{
				dim = *sh.GetInstanceAsType<Rocket::Core::Vector2i>(3);
			}
		}
	}

	Rocket::Core::Context* pRocketContext = Rocket::Core::CreateContext(name, dim);

	if (!pRocketContext)
	{
		return sh.ThrowError(_SC("Couldn't create the Context with name '%s'"), name.CString());
	}

	ContextInterface* pContext = NewInstance<ContextInterface>(v);

	pContext->m_pContext = pRocketContext;

	return 1;
}

void ContextInterface::Bind(HSQUIRRELVM vm)
{
	sq_pushroottable(vm);
	NamespaceHelper::switchTo(vm, "Rocket");


	sqb::ClassDefinition<ContextInterface> cCon(vm, -1, _SC("Context"));

	cCon.Constructor(&ContextInterface::constructor, sqb::FunctionOptions().ParamCheckCount(-2).TypeMask(_SC("xsx")));

	cCon.ClassFunction(&ContextInterface::Render, _SC("Render"));
	cCon.ClassFunction(&ContextInterface::Update, _SC("Update"));
	cCon.ClassFunction(&ContextInterface::GetName, _SC("GetName"));
	cCon.ClassFunction(&ContextInterface::GetDimensions, _SC("GetDimensions"));
	cCon.ClassFunction(&ContextInterface::SetDimensions, _SC("SetDimensions"));
	cCon.ClassFunction(&ContextInterface::LoadMouseCursor, _SC("LoadMouseCursor"));
	cCon.ClassFunction(&ContextInterface::LoadDocument, _SC("LoadDocument"));
	cCon.ClassFunction(&ContextInterface::CreateDocument, _SC("CreateDocument"));
	cCon.ClassFunction(&ContextInterface::UnloadDocument, _SC("UnloadDocument"));
	cCon.ClassFunction(&ContextInterface::UnloadAllDocuments, _SC("UnloadAllDocuments"));


	sq_poptop(vm);
}

void ContextInterface::InitialiseRocketInterface()
{
	ContextInstancer* instancer = new ContextInstancer();
	Rocket::Core::Factory::RegisterContextInstancer(instancer);
	instancer->RemoveReference();
}

bool ContextInterface::Render()
{
	return m_pContext->Render();
}

bool ContextInterface::Update()
{
	return m_pContext->Update();
}

const char* ContextInterface::GetName() const
{
	return m_pContext->GetName().CString();
}

const Rocket::Core::Vector2i& ContextInterface::GetDimensions() const
{
	return m_pContext->GetDimensions();
}

void ContextInterface::SetDimensions(const Rocket::Core::Vector2i& dim)
{
	return m_pContext->SetDimensions(dim);
}

ElementDocumentWrapper ContextInterface::__returnElementDocument(Rocket::Core::ElementDocument* rocketDoc) const
{
	ElementDocumentWrapper elemDoc;

	if (!rocketDoc)
	{
		rocketDoc = m_pContext->CreateDocument();
	}

	elemDoc.setElement(rocketDoc);

	return elemDoc;
}

ElementDocumentWrapper ContextInterface::LoadMouseCursor(const char* path)
{
	Rocket::Core::ElementDocument* rocketDoc = m_pContext->LoadMouseCursor(path);
	return __returnElementDocument(rocketDoc);
}

ElementDocumentWrapper ContextInterface::LoadDocument(const char* path)
{
	Rocket::Core::ElementDocument* rocketDoc = m_pContext->LoadDocument(path);
	return __returnElementDocument(rocketDoc);
}

void ContextInterface::UnloadAllDocuments()
{
	m_pContext->UnloadAllDocuments();
}

void ContextInterface::UnloadDocument(ElementDocumentWrapper& doc)
{

	m_pContext->UnloadDocument((Rocket::Core::ElementDocument*)doc.getElement());
}

ElementDocumentWrapper ContextInterface::CreateDocument(const char* tag)
{
	ElementDocumentWrapper elemDoc;

	elemDoc.setElement(m_pContext->CreateDocument());

	return elemDoc;
}




}
}
}