#include "RocketSquirrel.h"

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



namespace Rocket {
	namespace Squirrel {







		void Core::initialize()
		{

			HSQUIRRELVM v;

			v = sq_open(1024); //creates a VM with initial stack size 1024
    
			//do some stuff with squirrel here
    
			sq_close(v);

		}






	}
}