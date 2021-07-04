#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), windowTitle);
	view = window.getDefaultView();

	for (std::uint32_t i = 0; i < 32; i++)
	{
		CelestialBody *body = new CelestialBody();
		body->SetMass(std::rand() % 2001 + 10);
		body->SetPosition(sf::Vector2f(std::rand() % 10'001 - 5000, std::rand() % 10'001 - 5000));
		body->SetRadius(body->GetMass() / 100.0f);
		body->SetVelocity(sf::Vector2f(std::rand() % 501 - 250, std::rand() % 501 - 250));
		body->SetPathVisible(true);

		if (i == 0)
		{
			body->SetMass(1'000'000.0f);
			body->SetRadius(100.0f);
			body->SetVelocity(sf::Vector2f());
		}

		world.AddBody(body);
	}
}

void Game::Run()
{
	while (window.isOpen())
	{
		float speed = 1.0f;
		dt = deltaTime.restart().asSeconds();

		this->HandleEvents();

		window.clear();

		this->HandleViewControls();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		{
			speed = 5.0f;
		}

		if (start != sf::Vector2f(-1.0f, -1.0f))
		{
			sf::VertexArray line(sf::LineStrip);
			line.append(start);
			line.append(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			window.draw(line);
		}

		world.Update(dt * speed);
		world.Render(window);

		window.setView(view);
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

			case sf::Event::MouseButtonPressed:
				start = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				break;

			case sf::Event::MouseButtonReleased:
			{
				CelestialBody *body = new CelestialBody();
				body->SetPosition(start);
				body->SetVelocity(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - start);
				body->SetMass(1000.0f);
				body->SetRadius(25.0f);
				body->SetPathVisible(true);
				world.AddBody(body);

				start = sf::Vector2f(-1.0f, -1.0f);
			}	break;

			default:
				break;
		}
	}
}

void Game::HandleViewControls()
{
	const float zoomSpeed = 1.0f;
	float cameraSpeed = 1000.0f;

	// View movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		cameraSpeed *= 5.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
	{
		cameraSpeed /= 5.0f;
	}

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