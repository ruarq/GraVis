#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.hpp"
#include "RunningState.hpp"
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

private:
	GameState *state = nullptr;
	sf::RenderWindow window;

	const std::string windowTitle = "Gravity Visualization - C++ & SFML2.5.1";
	sf::Clock deltaTime, windowTitleUpdate;
	float dt = 0.0f;
};