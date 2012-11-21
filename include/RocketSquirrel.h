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


#ifndef __ROCKETSQUIRREL_INCLUDED
#define __ROCKETSQUIRREL_INCLUDED

#define ROCKETSQUIRRELDLL_API



#include "Rocket/Core.h"
#include "Rocket/Core/Plugin.h"
#include <squirrel.h>

namespace Rocket {
	namespace Squirrel {


		



		class ROCKETSQUIRRELDLL_API Module : public Rocket::Core::Plugin
		{
		private:

			void OnInitialise();
			void OnShutdown();

			static Module* s_pInstance;
			HSQUIRRELVM mVM;
			const bool mUseNamespace;
			bool mVMCreated;
			bool mInitialized;

		public:

			/*! Module entry point
			 * @param vm Squirrel Virtual Machine, if NULL then it will be created internally
			 * @param useNamespace If this is true, then every single class and type would be put in 
			 * Rocket.Core.$class/Type, usefull if you're also doing binding with the vm
			 */
			Module(HSQUIRRELVM vm = NULL, bool useNamespace = false);
			~Module();

			/*! Gets the instance (itself)*/
			static Module& instance();

			/*! True if the binding was done with a namespace */
			bool isUsingNamespace() const;

			/*! True if the binding was done with a namespace */
			HSQUIRRELVM getSquirrelVM() const;

		};





	}
}



#endif