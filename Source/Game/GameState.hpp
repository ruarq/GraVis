#pragma once

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
public:
	virtual ~GameState() = default;

public:
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() = 0;

	GameState* NextState() const;

	virtual void OnEvent(const sf::Event &event) {}

protected:
	GameState *nextState = nullptr;
};