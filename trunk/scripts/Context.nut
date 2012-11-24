local context = Rocket.Context("MyContext");
local context2 = Rocket.Context("MyContext2", Rocket.Vector2i(100, 200));

try {
	print("\nTrying to create a context with an existent name");
	local context = Rocket.Context("MyContext", Rocket.Vector2i(100, 200));

} catch (e)
{
	print("\nHandled Exception: " + e + "\n");
}