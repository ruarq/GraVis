#include "World.hpp"

#include "CelestialBody.hpp"

World::~World()
{
	for (CelestialBody* body : celestialBodies)
	{
		delete body;
	}
}

void World::Update(const float deltaTime)
{
	for (auto itr = celestialBodies.begin(); itr != celestialBodies.end();)
	{
		for (auto jtr = itr + 1; jtr != celestialBodies.end(); jtr++)
		{
			// Update gravity
			(*itr)->UpdateGravity(**jtr, deltaTime);
			(*jtr)->UpdateGravity(**itr, deltaTime);

			// Check collision
			if ((*itr)->Intersect(**jtr))
			{
				// Merge
				if ((*itr)->GetRadius() >= (*jtr)->GetRadius())
				{
					(*itr)->Merge(**jtr);
				}
				else
				{
					(*jtr)->Merge(**itr);
				}
			}
		}

		(*itr)->Update(deltaTime);

		// Remove dead bodies
		if (!(*itr)->GetAlive())
		{
			delete *itr;
			itr = celestialBodies.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void World::Render(sf::RenderWindow &window)
{
	for (CelestialBody* body : celestialBodies)
	{
		body->Render(window);
	}
}

void World::AddBody(const CelestialBody &body)
{
	celestialBodies.push_back(new CelestialBody(body));
}