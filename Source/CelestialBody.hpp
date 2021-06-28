#pragma once

#include <SFML/Graphics.hpp>

#include "Math.hpp"

class CelestialBody final
{
public:
	static constexpr float G = 100.0f;

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void UpdateGravity(const CelestialBody &otherBody, const float deltaTime);

	void SetPosition(const sf::Vector2f &position);
	sf::Vector2f GetPosition() const;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

	void SetMass(const float mass);
	float GetMass() const;

	void SetRadius(const float radius);
	float GetRadius() const;

private:
	sf::Vector2f position, velocity;
	float mass = 0.0f, radius = 0.0f;
};