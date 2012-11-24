print("\n\n :: StringList Tests :: \n\n");

local list = StringList();

local str = RocketString("Hello");

local str2 = RocketString(50);
local str3 = RocketString(1.5999);

//str2 = str2 + " Float + string";

str2 = RocketString(str3 + " STR");

local sqStr = "SquirrelString";

str.Clear();
str.Set(sqStr);

list[0] = str;
list[1] = str2;
list[2] = RocketString(-100.0);
list[3] = str3;

list.append(str);
list.push(str);

if (list.Contains(RocketString("Hello")))
{
	print("\nlist contains Hello\n"); 
}

function printList()
{
	print("\n");
	for (local i = 0; i < list.len(); i+=1)
	{
		print(" -> " + list[i] + "\n");
	}
}


printList();

print("\n Removing \n");
list.remove(0);
list.remove(4);

printList();