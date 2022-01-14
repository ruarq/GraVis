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

template<typename Iter>
void UpdateBodiesMT(World *world, const float deltaTime, Iter subBegin, Iter subEnd, Iter begin, Iter end)
{
	for (auto itr = subBegin; itr != subEnd; ++itr)
	{
		if (!(*itr)->IsAlive())
		{
			continue;
		}

		for (auto jtr = begin; jtr != end; ++jtr)
		{
			if (itr == jtr || !(*jtr)->IsAlive())
			{
				continue;
			}

			// Update gravity
			(*jtr)->UpdateGravity(*world, **itr, deltaTime);

			// Check collision
			if ((*itr)->Intersect(**jtr))
			{
				// Merge
				if ((*itr)->GetRadius() >= (*jtr)->GetRadius())
				{
					(*itr)->Merge(**jtr);
				}
			}
		}

		(*itr)->Update(*world, deltaTime);
	}
}

void World::Update(const float deltaTime)
{
	// Remove dead bodies from last update
	for (CelestialBody *deadBody : deadBodies)
	{
		delete deadBody;
	}
	deadBodies.clear();

	// update the bodies
	const int numThreads = 8;
	const auto shareSize = celestialBodies.size() / numThreads;
	std::vector<std::thread> threads;
	for (int i = 0; i < numThreads - 1; ++i)
	{
		auto subBegin = celestialBodies.begin() + shareSize * i;
		auto subEnd = celestialBodies.begin() + shareSize * (i + 1);

		threads.push_back(std::thread(
			UpdateBodiesMT<std::vector<CelestialBody*>::iterator>,
			this, deltaTime,
			subBegin, subEnd,
			celestialBodies.begin(), celestialBodies.end()));
	}

	threads.push_back(std::thread(
			UpdateBodiesMT<std::vector<CelestialBody*>::iterator>,
			this, deltaTime,
			celestialBodies.begin() + shareSize * (numThreads - 1), celestialBodies.end(),
			celestialBodies.begin(), celestialBodies.end()));

	for (auto &thread : threads)
	{
		thread.join();
	}

	// erase dead bodies
	for (auto itr = celestialBodies.begin(); itr != celestialBodies.end();)
	{
		if (!(*itr)->IsAlive())
		{
			deadBodies.push_back(*itr);
			itr = celestialBodies.erase(itr);
		}
		else
		{
			++itr;
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

void World::SetG(const float G)
{
	this->G = G;
}

float World::GetG() const
{
	return G;
}