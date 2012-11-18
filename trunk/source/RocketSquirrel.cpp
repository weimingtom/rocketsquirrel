#include "RocketSquirrel.h"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "squirrel.h"
#include <sqstdblob.h>
#include <sqstdsystem.h>
#include <sqstdio.h>
#include <sqstdmath.h>	
#include <sqstdstring.h>
#include <sqstdaux.h>

#include <sqrat.h>

#include <Rocket/Core.h>

namespace Rocket {
	namespace Squirrel {



		static HSQUIRRELVM g_vm = 0x0;


		class PrivateModule {
		};


		Module::Module(HSQUIRRELVM vm) :
			m_pPrivate(new PrivateModule(this))
		{
			if (vm)
			{
			}
			else
			{
				g_vm = vm;
			}
		}

		void Module::OnInitialise()
		{
			return;
		}




		void printFunc(HSQUIRRELVM v,const SQChar *s,...)
		{
			va_list vl;
			va_start(vl, s);
			vfprintf(stdout, s, vl);
			va_end(vl);
		}

		void compilerErrorFunc(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
		{
			std::cout << "Source: " << source << " Line: " << line << std::endl;
			std::cout << std::endl << desc << std::endl;
		}

		SQInteger file_lexfeedASCII(SQUserPointer file)
		{
			int ret;
			char c;
			if( ( ret=fread(&c,sizeof(c),1,(FILE *)file )>0) )
				return c;
			return 0;
		}

		int compile_file(HSQUIRRELVM v,const char *filename)
		{
			FILE *f=fopen(filename,"rb");
			if(f)
			{
				 SQRESULT r = sq_compile(v,file_lexfeedASCII,f,filename,1);

				 r;

				 fclose(f);
				 return 1;
			}
			return 0;
		}



		void myFunc() { }

		class MyClass {
		public:

			MyClass()
			{
				std::cout << "MyClass" << std::endl;
			}

			void Foo() { std::cout << "Hello this is C++" << std::endl;  }
			int bar;
		};

		void BindSquirrel(HSQUIRRELVM vm) {

			Sqrat::Table myTable(vm);
			myTable.Func("MyFunc", &myFunc);
		
			Sqrat::Class<MyClass> myClass(vm);
			myClass.Func("Foo", &MyClass::Foo);
			myClass.Var("bar", &MyClass::bar);
		
			Sqrat::RootTable(vm).Bind("MyTable", myTable);
			Sqrat::RootTable(vm).Bind("MyClass", myClass);
		}



		/*void Core::initialize()
		{
			std::cout << "Compiling Script: " << std::endl;



			HSQUIRRELVM v;

			v = sq_open(1024);

			SQCOMPILERERROR;

			sq_setcompilererrorhandler(v, &compilerErrorFunc);

			sq_setprintfunc(v, &printFunc, &printFunc);

			//compile_file(v, "test.nut");


			std::string strScript = " local obj = MyClass(); obj.Foo();      ";


			BindSquirrel(v);

			sq_compilebuffer(v, strScript.c_str(), strScript.size(), "Script.nut", true);

			//Execute the entry function
			sq_pushroottable(v);
			sq_call(v, 1, SQFalse, SQTrue);
    
			sq_close(v);

			Rocket::Core::RegisterPlugin(new Module());

		}*/
		




	}
}