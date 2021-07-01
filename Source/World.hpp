#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class CelestialBody;

class World final
{
public:
	~World();

public:
	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void AddBody(const CelestialBody &body);

// private:
	std::vector<CelestialBody*> celestialBodies;
};