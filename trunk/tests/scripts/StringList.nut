print("\n\n :: StringList Tests :: \n\n");

local list = Rocket.StringList();

local str = Rocket.String("Hello");

local str2 = Rocket.String(50);
local str3 = Rocket.String(1.5999);

//str2 = str2 + " Float + string";

str2 = Rocket.String(str3 + " STR");

local sqStr = "SquirrelString";

str.Clear();
str.Set(sqStr);

list[0] = str;
list[1] = str2;
list[2] = Rocket.String(-100.0);
list[3] = str3;

list.append(str);
list.push(str);

if (list.Contains(Rocket.String("Hello")))
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