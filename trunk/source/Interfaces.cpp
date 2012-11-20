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


#include <sqbind/sqbBind.h>



namespace Rocket {
	namespace Squirrel {





		void printFunc(HSQUIRRELVM v,const SQChar *s,...)
		{
			va_list vl;
			va_start(vl, s);

			char text[1024];

			vsnprintf(text, 1024, s, vl);

			vfprintf(stdout, s, vl);
#ifdef _WINDOWS
			OutputDebugStringA(text);
#endif
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



		SQInteger print_args(HSQUIRRELVM v)
		{
			SQInteger nargs = sq_gettop(v); //number of arguments
			for(SQInteger n=1;n<=nargs;n++)
			{
				printf("arg %d is ",n);
				switch(sq_gettype(v,n))
				{
					case OT_NULL:
						printf("null");        
						break;
					case OT_INTEGER:
						printf("integer");
						break;
					case OT_FLOAT:
						printf("float");
						break;
					case OT_STRING:
						printf("string");
						break;    
					case OT_TABLE:
						printf("table");
						break;
					case OT_ARRAY:
						printf("array");
						break;
					case OT_USERDATA:
						printf("userdata");
						break;
					case OT_CLOSURE:        
						printf("closure(function)");    
						break;
					case OT_NATIVECLOSURE:
						printf("native closure(C function)");
						break;
					case OT_GENERATOR:
						printf("generator");
						break;
					case OT_USERPOINTER:
						printf("userpointer");
						break;
					case OT_CLASS:
						printf("class");
						break;
					case OT_INSTANCE:
						printf("instance");
						break;
					case OT_WEAKREF:
						printf("weak reference");
						break;
					default:
						return sq_throwerror(v,"invalid param"); //throws an exception
				}
				printf("\n");
			}
			printf("\n\n");
			sq_pushinteger(v,nargs); //push the number of arguments as return value
			return 1; //1 because 1 value is returned
		}

		void RegisterSquirrelInterfaces()
		{
			//debug
			vm = sq_open(10024);

			sq_setcompilererrorhandler(vm, &compilerErrorFunc);

			sq_setprintfunc(vm, &printFunc, &printFunc);

			


			Sqrat::Script script(vm);
				
			Sqrat::string error;

			if (!script.CompileString(" local obj = MyClass(); print_args(\"hello\", 1.0, -100, obj); print(obj); ", error))
			{
				return;
			}


			try 
			{
				script.Run();
			}
			catch (Sqrat::Exception& e)
			{
				std::cout << "Sqrat::Exception: " << e.Message() << std::endl;
				return;
			}


			return;
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

			
			//Vector2i
			Sqrat::Class<Rocket::Core::Vector2i> classVector2i(vm);

			classVector2i.Var("x", &Rocket::Core::Vector2i::x);
			classVector2i.Var("y", &Rocket::Core::Vector2i::y);
			classVector2i.Overload("_mul", &Rocket::Core::Vector2i::operator*);
			classVector2i.Overload("_div", &Rocket::Core::Vector2i::operator/);
			classVector2i.Overload("_add", &Rocket::Core::Vector2i::operator+);
			classVector2i.Overload<Rocket::Core::Vector2i (Rocket::Core::Vector2i::*)(const Rocket::Core::Vector2i&) const>("_sub", &Rocket::Core::Vector2i::operator-);
			classVector2i.Overload("_cmp", &Rocket::Core::Vector2i::operator==);

			Sqrat::RootTable(vm).Bind("Vector2i", classVector2i);



			//Colourf
			Sqrat::Class<Rocket::Core::Colourf> classColourf(vm);

			classColourf.Var("red", &Rocket::Core::Colourf::red);
			classColourf.Var("green", &Rocket::Core::Colourf::green);
			classColourf.Var("blue", &Rocket::Core::Colourf::blue);
			classColourf.Var("alpha", &Rocket::Core::Colourf::alpha);
			classColourf.Overload("_cmp", &Rocket::Core::Colourf::operator==);

			Sqrat::RootTable(vm).Bind("Colourf", classColourf);




			//Colourb
			Sqrat::Class<Rocket::Core::Colourb> classColourb(vm);

			classColourb.Var("red", &Rocket::Core::Colourb::red);
			classColourb.Var("green", &Rocket::Core::Colourb::green);
			classColourb.Var("blue", &Rocket::Core::Colourb::blue);
			classColourb.Var("alpha", &Rocket::Core::Colourb::alpha);
			//classColourb.Overload("_cmp", &Rocket::Core::Colourb::operator==);
			//classColourb.Overload("_add", &Rocket::Core::Colourb::operator+);
			//classColourb.Overload<Rocket::Core::Colourb (Rocket::Core::Colourb::*)(float) const>("_mul", &Rocket::Core::Colourb::operator*);

			Sqrat::RootTable(vm).Bind("Colourb", classColourb);

		}



		void TestSquirrel()
		{
		}


		void TestInsterfaces()
		{
			return;
			Sqrat::Script script(vm);
				
			Sqrat::string error;

			if (!script.CompileFile("./testingscripts/interfaces.nut", error))
			{
				return;
			}


			try 
			{
				script.Run();
			}
			catch (Sqrat::Exception& e)
			{
				std::cout << "Sqrat::Exception: " << e.Message() << std::endl;
				return;
			}
		}






	}
}