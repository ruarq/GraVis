#pragma once

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "CelestialBody.hpp"
#include "GameState.hpp"

class RunningState final : public GameState
{
public:
	RunningState();

public:
	GameState* Update(const float deltaTime) override;
	void Render(sf::RenderWindow &window) override;

	void OnEvent(const sf::Event &event) override;

private:
	void HandleViewControls(const float deltaTime);

private:
	World world;
	sf::View view;
};