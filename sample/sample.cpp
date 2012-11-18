#include <iostream>
#include <string>
#include "RocketSquirrel.h"
#include <SFML/Window.hpp>

int main()
{
	sf::Window MyWindow(sf::VideoMode(800, 600), "RocketSquirrel (Squirrel Script for libRocket) Sample");


	Rocket::Squirrel::Core::initialize();

	std::string strin;

	std::cin >> strin;

	return 0;
}