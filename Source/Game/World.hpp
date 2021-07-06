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

	/**
	 * @brief Get a body from the world using world coordinates
	 * @param position The position in world coordinates
	 * @return Pointer to celestial body object or nullptr if there is no object at the position
	 */
	CelestialBody* GetBodyAt(const sf::Vector2f &position);

	float GetG() const;

private:
	std::vector<CelestialBody*> celestialBodies;
	std::vector<CelestialBody*> deadBodies;

	float G = 10.0f;
};