#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(1280u, 720u), windowTitle);
	view = window.getDefaultView();

	for (std::uint32_t i = 0; i < 512; i++)
	{
		CelestialBody *body = new CelestialBody();
		body->SetMass(std::rand() % 2001 + 10);
		body->SetPosition(sf::Vector2f(std::rand() % 10000, std::rand() % 10000));
		body->SetRadius(body->GetMass() / 100.0f);
		body->SetVelocity(sf::Vector2f(std::rand() % 101 - 50, std::rand() % 101 - 50));
		body->SetPathVisible(true);

		if (i == 0)
		{
			body->SetMass(5'000'000.0f);
			body->SetRadius(100.0f);
		}

		world.AddBody(body);
	}
}

void Game::Run()
{
	while (window.isOpen())
	{
		dt = deltaTime.restart().asSeconds();

		this->HandleEvents();

		window.clear();

		this->HandleViewControls();
		window.setView(view);

		world.Update(dt);
		world.Render(window);

		window.display();

		this->UpdateWindowTitle();
	}
}

void Game::UpdateWindowTitle()
{
	using namespace std::string_literals;

	if (windowTitleUpdate.getElapsedTime().asSeconds() >= 1.0f / windowTitleUpdateFreq)
	{
		window.setTitle(windowTitle + " - "s + std::to_string(int(1.0f / dt)) + " FPS"s);
		windowTitleUpdate.restart();
	}
}

void Game::HandleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::Resized:
				view.setSize(event.size.width, event.size.height);
				break;

			case sf::Event::MouseWheelScrolled:
				view.zoom(1.0f + float(event.mouseWheel.delta) * dt);
				break;

			default:
				break;
		}
	}
}

void Game::HandleViewControls()
{
	const float zoomSpeed = 1.0f;
	const float cameraSpeed = 500.0f;

	// View movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		view.move(0.0f, -cameraSpeed * dt);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		view.move(-cameraSpeed * dt, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		view.move(0.0f, cameraSpeed * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		view.move(cameraSpeed * dt, 0.0f);
	}

	// View zooming
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		view.zoom(1.0f - zoomSpeed * dt);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		view.zoom(1.0f + zoomSpeed * dt);
	}
}