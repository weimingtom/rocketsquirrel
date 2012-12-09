print("RocketSquirrel Test Cases \n\n");

function vector2fToStr(vec2f)
{
	return "{" + vec2f.x + ", " + vec2f.y + "}";
}

function printTestTitle(title)
{
	print("\n:: " + title + " :: \n\n");
}


//VECTOR2F
///////////////////////////////////////////////
///////////////////////////////////////////////
printTestTitle("Vector2f Testing");

local v2fa = Rocket.Vector2f(10.0, 5.0);
local v2fb = Rocket.Vector2f(10.0, 5.0);

function printVectors2f(title)
{
	print(title + "\n");
	print("v2fa = " + vector2fToStr(v2fa) + "\n");
	print("v2fb = " + vector2fToStr(v2fb) + "\n");
	print("\n");
}

//Start by printing their initial value
printVectors2f("Initial Value");



//Now lets test the vector2f methods

v2fa =  v2fb * 2;
v2fa *= 2;
printVectors2f("Mul");

v2fa = v2fa + v2fb;
printVectors2f("Add");

v2fa = v2fa - v2fb;
printVectors2f("Sub");

v2fb = v2fb / 2.0;
printVectors2f("Div");

if (v2fb != v2fa)
{
	printVectors2f("Cmp");
}

v2fa.Rotate(5.0);
printVectors2f("Rotate");

v2fb = v2fa.Normalise();
printVectors2f("Normalise");

v2fa *= v2fa.Magnitude();
printVectors2f("Magnitude");

v2fa *= v2fa.DotProduct(v2fb);
v2fb *= v2fa.DotProduct(v2fb);
printVectors2f("Dot");


//VECTOR2I
printTestTitle("Vector2i Testing");

local v2ia = Rocket.Vector2i();
local v2ib = Rocket.Vector2i(10, 10);

function printVectors2i(title)
{
	print(title + "\n");
	print("v2a = " + vector2fToStr(v2ia) + "\n");
	print("v2b = " + vector2fToStr(v2ib) + "\n");
	print("\n");
}

//Start by printing their initial value
printVectors2i("Initial Value");


//Now lets test the vector2f methods

v2ia =  v2ib * 2;
v2ia *= 2;
printVectors2i("Mul");

v2ia = v2ia + v2ib;
printVectors2i("Add");

v2ia = v2ia - v2ib;
printVectors2i("Sub");

v2ib = v2ib / 2.0;
printVectors2i("Div");

if (v2ib != v2ia)
{
	printVectors2i("Cmp");
}


//COLOURF
///////////////////////////////////////////////
///////////////////////////////////////////////
printTestTitle("Colourf Testing");

local colfa = Rocket.Colourf();
local colfb = Rocket.Colourf(0.4, 0.4, 0.3, 0.9);

colfa = colfb;

function printColour(col)
{
	print("Colour = {" + col.red + ", " + col.green + ", " + col.blue + ", " + col.alpha + "} \n");
}

printColour(colfa);

if (colfa == colfb)
{
	printColour(colfb);
}


//COLOURB
printTestTitle("Colourb Testing");

local colba = Rocket.Colourb();
local colbb = Rocket.Colourb(200, 100, 200, 255);

print("assing\n");
colba = colbb;

printColour(colbb);

print("\nCmp\n");
if (colbb == colba)
{
	printColour(colbb);
}

//URL
///////////////////////////////////////////////
///////////////////////////////////////////////
printTestTitle("URL Testing");

local url = Rocket.URL("http://google.com");

url.ClearParameters();

print(url);


//Log
///////////////////////////////////////////////
///////////////////////////////////////////////
printTestTitle("Log Testing");

Rocket.Log(Rocket.LogType.debug, "Debbuging interface OK!");

///////////////////////////////////////////////
///////////////////////////////////////////////

