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
	sf::View view = window.getView();

	std::vector<CelestialBody> celestialBodies;
	for (std::uint32_t i = 0; i < 4; i++)
	{
		CelestialBody body;
		body.SetMass(std::rand() % 901 + 100);

		body.SetPosition(sf::Vector2f(std::rand() % window.getSize().x, std::rand() % window.getSize().y));
		body.SetVelocity(sf::Vector2f(std::rand() % 201 - 100, std::rand() % 201 - 100));

		if (i == 0)
		{
			body.SetMass(10000);
			body.SetVelocity(sf::Vector2f(std::rand() % 11 - 5, std::rand() % 11 - 5));
		}

		body.SetRadius(body.GetMass() / 100.0f);

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
				}	break;

				default:
					break;
			}
		}

		window.clear();

		std::uint32_t i = 0;
		for (CelestialBody &body : celestialBodies)
		{
			for (CelestialBody &otherBody : celestialBodies)
			{
				if (&body != &otherBody)
				{
					body.UpdateGravity(otherBody, deltaTime);
				}
			}

			body.Update(deltaTime);
			// body.Render(window);

			// Wrap the position if neccessary
			if (body.GetPosition().x < 0.0f)
			{
				body.SetPosition(sf::Vector2f(window.getSize().x, body.GetPosition().y));
			}
			if (body.GetPosition().x > window.getSize().x)
			{
				body.SetPosition(sf::Vector2f(0.0f, body.GetPosition().y));
			}
			if (body.GetPosition().y < 0.0f)
			{
				body.SetPosition(sf::Vector2f(body.GetPosition().x, window.getSize().y));
			}
			if (body.GetPosition().y > window.getSize().y)
			{
				body.SetPosition(sf::Vector2f(body.GetPosition().x, 0.0f));
			}

			const std::string index = "["s + std::to_string(i) + "]"s;
			shader.setUniform("positions"s + index, sf::Glsl::Vec2(body.GetPosition().x, window.getSize().y - body.GetPosition().y));
			shader.setUniform("masses"s + index, body.GetMass());
			shader.setUniform("radii"s + index, body.GetRadius());
			i++;
		}

		window.draw(shaderSprite, &shader);
		window.display();

		if (titleUpdateClock.getElapsedTime().asSeconds() >= titleUpdateTime)
		{
			titleUpdateClock.restart();
			window.setTitle("Gravity Visualisation - C++ & SFML2.5.1 - FPS: "s
		 		+ std::to_string(static_cast<std::int32_t>(1.0f / deltaTime)));
		}
	}

	return 0;
}