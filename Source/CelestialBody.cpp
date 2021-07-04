#include "CelestialBody.hpp"

void CelestialBody::Update(World &world, const float deltaTime)
{
	if (pathVisible)
	{
		this->UpdatePath();
	}

	prevPosition = position;
	position += velocity * deltaTime;

	distanceTravelled += Distance(position, prevPosition);
}

void CelestialBody::Render(sf::RenderWindow &window)
{
	sf::CircleShape shape;
	shape.setRadius(radius);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(position);
	shape.setFillColor(bodyColor);
	window.draw(shape);

	if (pathVisible)
	{
		sf::VertexArray pathArray(sf::PrimitiveType::LineStrip);

		for (const sf::Vector2f &position : path)
		{
			pathArray.append(position);
		}

		pathArray.append(position);

		window.draw(pathArray);
	}
}

void CelestialBody::UpdateGravity(CelestialBody &otherBody, const float deltaTime) const
{
	const float distance = Distance(position, otherBody.position);

	if (distance != 0.0f)
	{
		const float force = -G * (otherBody.mass * mass) / (distance * distance);
		const sf::Vector2f acceleration = Normalized(otherBody.position - position) * (force / otherBody.mass);
		otherBody.velocity += acceleration * deltaTime;
	}
}

bool CelestialBody::Intersect(const CelestialBody &otherBody) const
{
	return Distance(position, otherBody.position) <= radius + otherBody.radius;
}

void CelestialBody::Merge(CelestialBody &otherBody)
{
	// Calculate the radius after the merge
	const float volume = mass / this->GetDensity() + otherBody.mass / otherBody.GetDensity();
	radius = Root(volume / ((4.0f / 3.0f) * float(M_PI)), 3.0f);

	// Calculate the velocity after the merge
	velocity = ((mass * velocity) + (otherBody.mass * otherBody.velocity)) / (mass + otherBody.mass);

	mass += otherBody.mass;

	otherBody.SetAlive(false);
}

void CelestialBody::SetPosition(const sf::Vector2f &position)
{
	this->position = position;
}

sf::Vector2f CelestialBody::GetPosition() const
{
	return position;
}

void CelestialBody::SetVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

sf::Vector2f CelestialBody::GetVelocity() const
{
	return velocity;
}

void CelestialBody::SetMass(const float mass)
{
	this->mass = mass;
}

float CelestialBody::GetMass() const
{
	return mass;
}

void CelestialBody::SetRadius(const float radius)
{
	this->radius = radius;
}

float CelestialBody::GetRadius() const
{
	return radius;
}

float CelestialBody::GetDensity() const
{
	return mass / ((4.0f / 3.0f) * M_PI * std::pow(radius, 3.0f));
}

void CelestialBody::SetAlive(const bool alive)
{
	this->alive = alive;
}

bool CelestialBody::IsAlive() const
{
	return alive;
}

void CelestialBody::SetBodyColor(const sf::Color &color)
{
	bodyColor = color;
}

void CelestialBody::SetPathVisible(const bool visible)
{
	pathVisible = visible;
}

void CelestialBody::UpdatePath()
{
	if (distanceTravelled >= pathUpdateDistance)
	{
		path.push_back(position);
		pathUpdate.restart();
		distanceTravelled = 0.0f;
	}

	if (path.size() > pathResolution)
	{
		path.erase(path.begin());
	}
}
