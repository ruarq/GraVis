#pragma once

#include <SFML/Graphics.hpp>

#include "Math.hpp"

class CelestialBody final
{
public:
	static constexpr float G = 10.0f;

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void UpdateGravity(const CelestialBody &otherBody, const float deltaTime);

	bool Intersect(const CelestialBody &otherBody) const;
	void Merge(CelestialBody &otherBody);

	void SetPosition(const sf::Vector2f &position);
	sf::Vector2f GetPosition() const;

	void SetVelocity(const sf::Vector2f &velocity);
	sf::Vector2f GetVelocity() const;

	void SetMass(const float mass);
	float GetMass() const;

	void SetRadius(const float radius);
	float GetRadius() const;

	float GetDensity() const;

	void SetAlive(const bool alive);
	bool GetAlive() const;

private:
	sf::Vector2f position, velocity;
	float mass = 0.0f, radius = 0.0f;
	bool alive = true;
};