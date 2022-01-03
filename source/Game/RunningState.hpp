#pragma once

#include <SFML/Graphics.hpp>

#include "Mui/Mui.hpp"

#include "World.hpp"
#include "CelestialBody.hpp"
#include "GameState.hpp"

class RunningState final : public GameState
{
public:
	RunningState(sf::RenderWindow &window);

public:
	GameState* Update(const float deltaTime) override;
	void Render() override;

	void OnEvent(const sf::Event &event) override;

private:
	void UpdateView(const float deltaTime);

private:
	// temporary, delete later
	float bodySize = 100.0f;

	sf::RenderWindow &window;
	sf::View view;
	float cameraFollowSpeed = 16.0f;
	float currentZoom = 1.0f;

	Mui::Context uiContext;

	World world;
	CelestialBody *bodyToFollow = nullptr;

	bool isPaused = false;

	sf::Vector2f mouseDragStart;
	bool isDragging = false;
};