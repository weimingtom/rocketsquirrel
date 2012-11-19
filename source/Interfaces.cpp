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


#include <Rocket/Core/URL.h>
#include <Rocket/Core/Log.h>
#include <Rocket/Core/Dictionary.h>
/*#include <Rocket/Core/Python/ConverterScriptObject.h>
#include <Rocket/Core/Python/PickleTypeConverter.h>
#include <Rocket/Core/Python/Utilities.h>
#include <Rocket/Core/Python/VectorInterface.h>*/
#include <vector>
#include <squirrel.h>
#include <sqrat.h>


#include <iostream>


#include <Windows.h>

namespace Rocket {
	namespace Squirrel {



		void printFunc(HSQUIRRELVM v,const SQChar *s,...)
		{
			va_list vl;
			va_start(vl, s);

			char text[1024];

			vsnprintf(text, 1024, s, vl);

			vfprintf(stdout, s, vl);

			OutputDebugStringA(text);

			va_end(vl);
		}

		void compilerErrorFunc(HSQUIRRELVM v, const SQChar* desc, const SQChar* source, SQInteger line, SQInteger column)
		{
			std::cout << "Source: " << source << " Line: " << line << std::endl;
			std::cout << std::endl << desc << std::endl;

			OutputDebugString(desc);
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

			/*Sqrat::Table myTable(vm);
			myTable.Func("MyFunc", &myFunc);
		
			Sqrat::Class<MyClass> myClass(vm);
			myClass.Func("Foo", &MyClass::Foo);
			myClass.Var("bar", &MyClass::bar);
		
			Sqrat::RootTable(vm).Bind("MyTable", myTable);
			Sqrat::RootTable(vm).Bind("MyClass", myClass);*/



			Sqrat::Class<Rocket::Core::Vector2f> classVector2f(vm);


			//Rocket::Core::Vector2f (*func)(operator-(const Rocket::Core::Vector2f&) const) = Rocket::Core::Vector2f::operator-;

			typedef Rocket::Core::Vector2f (Rocket::Core::Vector2f::* Vector2fSubOperator)(const Rocket::Core::Vector2f&) const;

			classVector2f.Var("x", &Rocket::Core::Vector2f::x);
			classVector2f.Var("y", &Rocket::Core::Vector2f::y);
			classVector2f.Overload("_mul", &Rocket::Core::Vector2f::operator*);
			classVector2f.Overload("_div", &Rocket::Core::Vector2f::operator/);
			classVector2f.Overload("_add", &Rocket::Core::Vector2f::operator+);
			classVector2f.Overload("_sub", (Vector2fSubOperator)&Rocket::Core::Vector2f::operator-);
			classVector2f.Overload("_cmp", &Rocket::Core::Vector2f::operator==);
			classVector2f.Func("DotProduct", &Rocket::Core::Vector2f::DotProduct);
			classVector2f.Func("Normalise", &Rocket::Core::Vector2f::Normalise);
			classVector2f.Func("Rotate", &Rocket::Core::Vector2f::Rotate);
			classVector2f.Func("Magnitude", &Rocket::Core::Vector2f::Magnitude);



			Sqrat::RootTable(vm).Bind("Vector2f", classVector2f);



		}
		HSQUIRRELVM vm;


		void RegisterSquirrelInterfaces()
		{
			//debug
			vm = sq_open(1024);

			sq_setcompilererrorhandler(vm, &compilerErrorFunc);

			sq_setprintfunc(vm, &printFunc, &printFunc);


			//Vector2f
			Sqrat::Class<Rocket::Core::Vector2f> classVector2f(vm);

			classVector2f.Var("x", &Rocket::Core::Vector2f::x);
			classVector2f.Var("y", &Rocket::Core::Vector2f::y);
			classVector2f.Overload("_mul", &Rocket::Core::Vector2f::operator*);
			classVector2f.Overload("_div", &Rocket::Core::Vector2f::operator/);
			classVector2f.Overload("_add", &Rocket::Core::Vector2f::operator+);
			classVector2f.Overload<Rocket::Core::Vector2f (Rocket::Core::Vector2f::*)(const Rocket::Core::Vector2f&) const>("_sub", &Rocket::Core::Vector2f::operator-);
			classVector2f.Overload("_cmp", &Rocket::Core::Vector2f::operator==);
			classVector2f.Overload("DotProduct", &Rocket::Core::Vector2f::DotProduct);
			classVector2f.Overload("Rotate", &Rocket::Core::Vector2f::Rotate);
			classVector2f.Func("Normalise", &Rocket::Core::Vector2f::Normalise);
			classVector2f.Func("Magnitude", &Rocket::Core::Vector2f::Magnitude);

			Sqrat::RootTable(vm).Bind("Vector2f", classVector2f);



			python::class_< Vector2i >("Vector2i")
		.def(python::init< int, int >())
		.def_readwrite("x", &Vector2i::x)
		.def_readwrite("y", &Vector2i::y)
		.def(python::self * int())		 // * int
		.def(python::self / int())		 // / int
		.def(python::self + Vector2i())	 // + Vector2i
		.def(python::self - Vector2i())	 // - Vector2i
		.def(python::self == Vector2i()) // ==
		.def(python::self != Vector2i()) // !=
		.def_pickle(PickleTypeConverter< Vector2i >())

			return;

		}



		void TestSquirrel()
		{
			std::string strScript = " local v = Vector2f(); local v2 = Vector2f(); print(v.DotProduct(v2)); print(v.x);      ";


			try {
				Sqrat::Script script(vm);
				
				Sqrat::string error;

				if (script.CompileString(strScript, error))
				{

					if (!script.Run(error))
					{
						return;
					}
				}

			} catch(Sqrat::Exception& e) {
				

				return;

			} catch(std::exception& e) {
				

				return;

			}

			//SQRESULT r;
			
			//r = sq_compilebuffer(vm, strScript.c_str(), strScript.size(), "Script.nut", true);

			//Execute the entry function
			//sq_pushroottable(vm);
			//r = sq_call(vm, 1, SQFalse, SQTrue);
		}




	}
}