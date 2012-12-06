print("\n\n :: Variant Tests :: \n\n");


local vari = Rocket.Variant("STR Variant");
print(vari + "\n");

vari = Rocket.Variant(100);
print(vari + "\n");

vari = Rocket.Variant(-99.0);
print(vari.tostring() + "\n");

print(10.0 * vari.tofloat() + "\n");

print(10.0 * vari.tointeger() + "\n");

vari = Rocket.Variant(Rocket.Vector2f(-66.07342, -20.0));

print(10.0 * vari.toVector2f().x + "\n");