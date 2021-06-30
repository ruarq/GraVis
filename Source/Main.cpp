#include <ctime>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "CelestialBody.hpp"

int main(int argc, char **argv)
{
	// Get the shader program
	std::string shaderFile(argv[1]);

	std::srand(std::time(nullptr));

	using namespace std::string_literals;

	sf::Clock programClock;
	sf::Clock titleUpdateClock;
	const float titleUpdateTime = 1.0f;
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1280u, 720u), "Gravity Visualisation - C++ & SFML2.5.1");
	sf::Vector2f camera;

	std::vector<CelestialBody> celestialBodies;
	for (std::uint32_t i = 0; i < 32; i++)
	{
		CelestialBody body;
		body.SetMass(std::rand() % 1001 + 100);
		body.SetPosition(sf::Vector2f(std::rand() % window.getSize().x, std::rand() % window.getSize().y));
		body.SetVelocity(sf::Vector2f(std::rand() % 11 - 5, std::rand() % 11 - 5));
		body.SetRadius(body.GetMass() / float(std::rand() % 200 + 100));

		celestialBodies.push_back(body);
	}

	sf::Shader shader;
	shader.loadFromFile(shaderFile, sf::Shader::Fragment);
	sf::Texture shaderTexture;
	shaderTexture.create(window.getSize().x, window.getSize().y);
	sf::Sprite shaderSprite(shaderTexture);

	shader.setUniform("numCelestialBodies", int(celestialBodies.size()));
	shader.setUniform("G", CelestialBody::G);
	shader.setUniform("pixelMass", 0.01f);

	if (!shader.isAvailable())
	{
		return 1;
	}

	while (window.isOpen())
	{
		const float deltaTime = frameClock.restart().asSeconds();

		shader.setUniform("time", programClock.getElapsedTime().asSeconds());

		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				
				case sf::Event::Resized:
				{
					shaderTexture.create(event.size.width, event.size.height);
					shaderSprite.setTexture(shaderTexture, true);
					
					sf::View view = window.getDefaultView();
					view.setSize(window.getSize().x, window.getSize().y);
					view.setCenter(view.getSize() / 2.0f);
					window.setView(view);
				}	break;

				default:
					break;
			}
		}

		window.clear();

		// Move the view
		const float cameraSpeed = 500.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			camera.y -= cameraSpeed * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			camera.x -= cameraSpeed * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			camera.y += cameraSpeed * deltaTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			camera.x += cameraSpeed * deltaTime;
		}

		// Update
		for (auto bodyItr = celestialBodies.begin(); bodyItr != celestialBodies.end();)
		{
			CelestialBody &body = *bodyItr;
			for (CelestialBody &otherBody : celestialBodies)
			{
				if (&body == &otherBody)
				{
					continue;
				}

				body.UpdateGravity(otherBody, deltaTime);

				if (body.Intersect(otherBody))
				{
					if (body.GetRadius() > otherBody.GetRadius())
					{
						body.Merge(otherBody);
					}
					else
					{
						otherBody.Merge(body);
					}
				}
			}

			body.Update(deltaTime);

			if (!body.GetAlive())
			{
				bodyItr = celestialBodies.erase(bodyItr);
			}
			else
			{
				bodyItr++;
			}
		}

		// Render
		shader.setUniform("numCelestialBodies", int(celestialBodies.size()));
		std::uint32_t i = 0;
		for (CelestialBody &body : celestialBodies)
		{
			const std::string index = "["s + std::to_string(i) + "]"s;
			shader.setUniform("positions"s + index,
				sf::Glsl::Vec2(
					body.GetPosition().x - camera.x,
					window.getSize().y - body.GetPosition().y + camera.y));
			shader.setUniform("masses"s + index, body.GetMass());
			shader.setUniform("radii"s + index, body.GetRadius());
			i++;
		}

		window.draw(shaderSprite, &shader);
		window.display();

		// Update title bar
		if (titleUpdateClock.getElapsedTime().asSeconds() >= titleUpdateTime)
		{
			titleUpdateClock.restart();
			window.setTitle("Gravity Visualisation - C++ & SFML2.5.1 - FPS: "s
		 		+ std::to_string(static_cast<std::int32_t>(1.0f / deltaTime)));
		}
	}

	return 0;
}