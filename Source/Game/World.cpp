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
	// Remove dead bodies from last update
	for (CelestialBody *deadBody : deadBodies)
	{
		delete deadBody;
	}
	deadBodies.clear();

	for (auto itr = celestialBodies.begin(); itr != celestialBodies.end();)
	{
		for (auto jtr = itr + 1; jtr != celestialBodies.end(); jtr++)
		{
			// Update gravity
			(*itr)->UpdateGravity(*this, **jtr, deltaTime);
			(*jtr)->UpdateGravity(*this, **itr, deltaTime);

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
			deadBodies.push_back(*itr);
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

CelestialBody* World::GetBodyAt(const sf::Vector2f &position)
{
	for (CelestialBody *body : celestialBodies)
	{
		if (Distance(position, body->GetPosition()) <= body->GetRadius())
		{
			return body;
		}
	}

	return nullptr;
}

float World::GetG() const
{
	return G;
}