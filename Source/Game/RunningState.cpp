#include "RunningState.hpp"

RunningState::RunningState(sf::RenderWindow &window)
	: window(window)
{
	for (std::uint32_t i = 0; i < 512; i++)
	{
		CelestialBody *body = new CelestialBody();
		body->SetMass(std::rand() % 2001 + 10);
		body->SetPosition(sf::Vector2f(std::rand() % 10'001 - 5000, std::rand() % 10'001 - 5000));
		body->SetRadius(body->GetMass() / 100.0f);
		body->SetVelocity(sf::Vector2f(std::rand() % 101 - 50, std::rand() % 101 - 50));
		body->SetPathVisible(true);
		body->SetPathLength(2048.0f);

		world.AddBody(body);
	}
}

GameState* RunningState::Update(const float deltaTime)
{
	if (!isPaused)
	{
		world.Update(deltaTime);
	}

	this->UpdateView(deltaTime);

	return nullptr;
}

void RunningState::Render()
{
	window.setView(view);
	world.Render(window);
}

void RunningState::UpdateView(const float deltaTime)
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

	// View zooming
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		view.zoom(1.0f - zoomSpeed * deltaTime);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		view.zoom(1.0f + zoomSpeed * deltaTime);
	}

	// View following body
	if (bodyToFollow)
	{
		sf::Vector2f direction = bodyToFollow->GetPosition() - view.getCenter();
		const float distance = Length(direction);
		direction = Normalized(direction);

		view.move(direction * distance / viewTransitionSpeed);

		if (!bodyToFollow->IsAlive())
		{
			bodyToFollow = nullptr;
		}
	}
}

void RunningState::OnEvent(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			break;

		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Button::Left:
					bodyToFollow = world.GetBodyAt(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
					break;

				default:
					break;
			}
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Key::W:
				case sf::Keyboard::Key::A:
				case sf::Keyboard::Key::S:
				case sf::Keyboard::Key::D:
					bodyToFollow = nullptr;
					break;
			}
			break;

		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
				case sf::Keyboard::Key::Space:
					isPaused = !isPaused;
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}
}