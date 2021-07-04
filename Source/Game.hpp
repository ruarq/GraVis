#pragma once

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "CelestialBody.hpp"

class Game final
{
public:
	constexpr static float windowTitleUpdateFreq = 1.0f;

public:
	Game();

public:
	void Run();

private:
	void UpdateWindowTitle();
	void HandleEvents();

	void HandleViewControls();

private:
	sf::RenderWindow window;
	sf::View view;
	World world;

	sf::Vector2f start = sf::Vector2f(-1.0f, -1.0f);

	sf::Clock deltaTime, windowTitleUpdate;
	float dt = 0.0f;

	const std::string windowTitle = "Gravity Visualization - C++ & SFML2.5.1";
};