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
	void UpdateWindowTitle(const float deltaTime);
	void HandleEvents();

	void HandleViewControls(const float deltaTime);

private:
	sf::RenderWindow window;
	sf::View view;
	World world;

	sf::Clock deltaTime, windowTitleUpdate;

	const std::string windowTitle = "Gravity Visualization - C++ & SFML2.5.1";
};