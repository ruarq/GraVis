#include <ctime>

#include <SFML/Graphics.hpp>

#include "CelestialBody.hpp"

int main()
{
	std::srand(std::time(nullptr));

	using namespace std::string_literals;

	sf::Clock programClock;
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1280u, 720u), "Gravity Visualisation - C++ & SFML2.5.1");

	std::vector<CelestialBody> celestialBodies;
	for (std::uint32_t i = 0; i < 8; i++)
	{
		CelestialBody body;
		body.SetMass(std::rand() % 901 + 100);

		body.SetPosition(sf::Vector2f(std::rand() % window.getSize().x, std::rand() % window.getSize().y));
		body.SetVelocity(sf::Vector2f(std::rand() % 51 - 25, std::rand() % 51 - 25));

		if (i == 0)
		{
			body.SetMass(std::rand() % 10001 + 50000);
			body.SetVelocity(sf::Vector2f(std::rand() % 11 - 5, std::rand() % 11 - 5));
		}

		celestialBodies.push_back(body);
	}
	
	sf::Shader shader;
	shader.loadFromFile("Shaders/Gravity.glsl", sf::Shader::Fragment);
	sf::Texture shaderTexture;
	shaderTexture.create(window.getSize().x, window.getSize().y);
	sf::Sprite shaderSprite(shaderTexture);

	if (!shader.isAvailable())
	{
		return 1;
	}

	shader.setUniform("numCelestialBodies", int(celestialBodies.size()));

	while (window.isOpen())
	{
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

		// Simulate
		// ...
		const float deltaTime = frameClock.restart().asSeconds();

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
			i++;
		}

		// Visualize
		window.clear();
		window.draw(shaderSprite, &shader);
		window.display();

		// using namespace std::string_literals;
		
		// window.setTitle("Gravity Visualisation - C++ & SFML2.5.1 - FPS: "s
		// 	+ std::to_string(static_cast<std::int32_t>(1.0f / deltaTime)));
	}

	return 0;
}