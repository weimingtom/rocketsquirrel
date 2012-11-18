/*
Copyright RocketSquirrel (c) 2012 Kuko

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#ifndef __ROCKETSQUIRREL_INCLUDED
#define __ROCKETSQUIRREL_INCLUDED

#define ROCKETSQUIRRELDLL_API

#include "Rocket/Core.h"
#include "Rocket/Core/Plugin.h"
#include <squirrel.h>

namespace Rocket {
	namespace Squirrel {


		class PrivateModule;


		class ROCKETSQUIRRELDLL_API Module : public Rocket::Core::Plugin
		{
		private:
			/// Hook for rocket plugin initialisation
			virtual void OnInitialise();

			PrivateModule* m_pPrivate;

		public:

			/*if vm is NULL then the module will create 
			 *a global squirrel virtual machine, for all
			 *context, tho you can assign a VM per context
			 *later on*/
			Module(HSQUIRRELVM vm = 0x0);
		};





	}
}



#endif