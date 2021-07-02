#pragma once

#include <SFML/Graphics.hpp>

#include "World.hpp"

class Game final
{
public:
	constexpr static float windowTitleUpdateFreq = 1.0f;

public:
	Game();

public:
	void Run();

private:
	void UpdateWindowTitle(const float deltaTime);
	void HandleEvents();

private:
	sf::RenderWindow window;
	World world;

	sf::Clock deltaTime, windowTitleUpdate;

	const std::string windowTitle = "Gravity Visualization - C++ & SFML2.5.1";
};