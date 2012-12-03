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
#include "EventWrapper.h"
#include "../BindingUtil.h"
#include "ElementWrapper.h"
#include "DictionaryInterface.h"


namespace Rocket {
namespace Core {
namespace Squirrel {



EventWrapper::EventWrapper(const EventWrapper& other) :
	m_pEvent(0x0)
{
	this->operator=(other);
}

EventWrapper::EventWrapper(Rocket::Core::Event* evt)
{
	evt->AddReference();
	m_pEvent = evt;
}

EventWrapper::EventWrapper() :
	m_pEvent(0x0)
{
}

EventWrapper::~EventWrapper()
{
	if (m_pEvent)
	{
		m_pEvent->RemoveReference();
	}
}

EventWrapper& EventWrapper::operator= (const EventWrapper& other)
{
	if (other.m_pEvent == 0x0)
	{
		return *this;
	}

	ROCKETSQUIRREL_ASSERT(m_pEvent == 0x0);

	m_pEvent = other.m_pEvent;
	m_pEvent->AddReference();

	return *this;
}

const char* EventWrapper::GetType() const
{
	return m_pEvent->GetType().CString();
}

ElementWrapper EventWrapper::GetTargetElement() const
{
	ElementWrapper wrapper;
	wrapper.setElement(m_pEvent->GetTargetElement());

	return wrapper;
}

ElementWrapper EventWrapper::GetCurrentElement() const
{
	ElementWrapper wrapper;
	wrapper.setElement(m_pEvent->GetCurrentElement());

	return wrapper;
}

DictionaryInterface EventWrapper::GetParameters() const
{
	DictionaryInterface dic;
	Rocket::Core::Dictionary& rocketDic = dic.GetRocketDictionary();
	rocketDic = (*m_pEvent->GetParameters());

	return dic;
}

void EventWrapper::StopPropagation()
{
	m_pEvent->StopPropagation();
}

void EventWrapper::Bind(HSQUIRRELVM vm)
{
	sqb::ClassDefinition<EventWrapper> cE(vm, -1, _SC("Event"));
	
	cE.Constructor(&NoConstructable);

	cE.ClassFunction(&EventWrapper::GetType, _SC("GetType"));
	cE.ClassFunction(&EventWrapper::GetTargetElement, _SC("GetTargetElement"));
	cE.ClassFunction(&EventWrapper::GetCurrentElement, _SC("GetCurrentElement"));
	cE.ClassFunction(&EventWrapper::GetParameters, _SC("GetParameters"));
	cE.ClassFunction(&EventWrapper::StopPropagation, _SC("StopPropagation"));

}






}
}
}