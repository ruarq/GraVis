#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
	virtual ~GameState() = default;

public:
	virtual GameState* Update(const float deltaTime) = 0;
	virtual void Render() = 0;

	virtual void OnEvent(const sf::Event &event) {}
};