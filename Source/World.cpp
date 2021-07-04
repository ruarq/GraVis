#include "World.hpp"

#include "CelestialBody.hpp"

World::~World()
{
}

void World::Destroy()
{
	for (CelestialBody* body : celestialBodies)
	{
		delete body;
	}

	celestialBodies.clear();
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

		(*itr)->Update(*this, deltaTime);

		// Remove dead bodies
		if (!(*itr)->IsAlive())
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

void World::AddBody(CelestialBody *body)
{
	celestialBodies.push_back(body);
}