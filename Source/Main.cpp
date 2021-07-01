#include <ctime>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "CelestialBody.hpp"

int main(int argc, char **argv)
{
	std::srand(std::time(nullptr));

	std::vector<sf::Vector2f> path;

	using namespace std::string_literals;
	sf::Shader shader;

	sf::Clock programClock;
	sf::Clock addToPath;
	const float addTopathTime = 0.1f;
	sf::Clock titleUpdateClock;
	const float titleUpdateTime = 1.0f;
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1280u, 720u), "Gravity Visualisation - C++ & SFML2.5.1");
	sf::View view = window.getDefaultView();

	World world;
	for (std::uint32_t i = 0; i < 2048; i++)
	{
		CelestialBody body;
		body.SetMass(std::rand() % 2001 + 200);
		body.SetPosition(sf::Vector2f(std::rand() % 10000, std::rand() % 10000));
		body.SetVelocity(sf::Vector2f(std::rand() % 11 - 5, std::rand() % 11 - 5));
		body.SetRadius(body.GetMass() / float(std::rand() % 200 + 100));

		world.AddBody(body);
	}

	CelestialBody *prevBody, *body = nullptr;
	while (window.isOpen())
	{
		prevBody = body;
		body = *std::max_element(world.celestialBodies.begin(), world.celestialBodies.end(), [](const CelestialBody *a, const CelestialBody *b)
		{
			return a->GetRadius() < b->GetRadius();
		});

		if (body != prevBody)
		{
			path.clear();
		}

		const float deltaTime = frameClock.restart().asSeconds();

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
					view.setSize(window.getSize().x, window.getSize().y);
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
			view.move(0.0f, -cameraSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			view.move(-cameraSpeed * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			view.move(0.0f, cameraSpeed * deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			view.move(cameraSpeed * deltaTime, 0.0f);
		}
		view.setCenter(body->GetPosition());

		// Zooming
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			view.zoom(0.995f - deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			view.zoom(1.005f + deltaTime);
		}

		window.setView(view);

		world.Update(deltaTime);
		world.Render(window);

		if (addToPath.getElapsedTime().asSeconds() >= addTopathTime)
		{
			path.push_back(body->GetPosition());

			if (path.size() > int(128.0f / addTopathTime))
			{
				path.erase(path.begin());
			}

			addToPath.restart();
		}

		sf::VertexArray array(sf::PrimitiveType::LineStrip);
		std::for_each(path.begin(), path.end(), [&](auto &pos)
		{
			array.append(pos);
		});
		array.append(body->GetPosition());
		window.draw(array);

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