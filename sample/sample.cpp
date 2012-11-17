#include <iostream>
#include <string>
#include "RocketSquirrel.h"

int main()
{

	Rocket::Squirrel::Core::initialize();

	std::cout << "RocketSquirrel" << " " << "OK" << std::endl;

	std::string strin;

	std::cin >> strin;

	return 0;
}