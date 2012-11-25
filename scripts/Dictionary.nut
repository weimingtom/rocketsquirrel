print("\n\n :: Dictionary Tests :: \n\n");

local dict = Rocket.Dictionary();

local vari = Rocket.Variant();

print("Set/[]\n");
dict["test"] = vari;

print("Size/Len \n");
print("Size = " + dict.len() + "\n");


print("Removing\n");
dict.remove("test");

try 
{
	dict["test"].test();
} catch (e)
{
	print("Handled Exception: " + e + "\n\n");
}

if (!dict.Contains("test"))
{
	print("Contains\n\n\n");
}