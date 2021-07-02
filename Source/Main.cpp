#include <iostream>
#include <exception>

#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "World.hpp"
#include "CelestialBody.hpp"

int main()
{
	// try
	{
		Game game;
		game.Run();
	}
	// catch (std::exception &e)
	// {
	// 	std::cerr << e.what() << "\n";
	// 	// return 1;
	// }

	return 0;
}