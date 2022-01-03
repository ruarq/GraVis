#include <iostream>
#include <exception>

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"

int main()
{
	std::srand(std::time(nullptr));

	try
	{
		Game game;
		game.Run();
	}
	catch (std::exception &e)
	{
	 	std::cerr << e.what() << "\n";
	 	return 1;
	}

	return 0;
}
