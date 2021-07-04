#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class CelestialBody;

class World final
{
public:
	~World();

public:
	void Destroy();

	void Update(const float deltaTime);
	void Render(sf::RenderWindow &window);

	void AddBody(CelestialBody *body);

private:
	std::vector<CelestialBody*> celestialBodies;
};