print("\n\n :: Dictionary Tests :: \n\n");

local dict = Dictionary();

local vari = Variant();

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
	print("Exception: " + e + "\n\n");
}

if (!dict.Contains("test"))
{
	print("Contains\n\n\n");
}