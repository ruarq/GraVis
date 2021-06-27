#include "CelestialBody.hpp"

void CelestialBody::Update(const float deltaTime)
{
	position += velocity * deltaTime;
}

void CelestialBody::Render(sf::RenderWindow &window)
{
}

void CelestialBody::UpdateGravity(const CelestialBody &otherBody, const float deltaTime)
{
	const float distance = Distance(position, otherBody.position);
	const float force = G * (mass * otherBody.mass) / (distance * distance);
	const sf::Vector2f acceleration = Normalized(otherBody.position - position) * (force / mass);
	velocity += acceleration * deltaTime;
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