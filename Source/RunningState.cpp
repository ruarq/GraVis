#include "RunningState.hpp"

RunningState::RunningState()
{
	for (std::uint32_t i = 0; i < 32; i++)
	{
		CelestialBody *body = new CelestialBody();
		body->SetMass(std::rand() % 2001 + 10);
		body->SetPosition(sf::Vector2f(std::rand() % 10'001 - 5000, std::rand() % 10'001 - 5000));
		body->SetRadius(body->GetMass() / 100.0f);
		body->SetVelocity(sf::Vector2f(std::rand() % 501 - 250, std::rand() % 501 - 250));
		body->SetPathVisible(true);

		// if (i ==31)
		// {
		// 	body->SetMass(5'000'000.0f);
		// 	body->SetRadius(100.0f);
		// 	body->SetVelocity(body->GetVelocity() * 0.2f);
		// }

		world.AddBody(body);
	}
}

GameState* RunningState::Update(const float deltaTime)
{
	this->HandleViewControls(deltaTime);
	world.Update(deltaTime);

	return nullptr;
}

void RunningState::Render(sf::RenderWindow &window)
{
	window.setView(view);
	world.Render(window);
}

void RunningState::HandleViewControls(const float deltaTime)
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
}

void RunningState::OnEvent(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			break;

		default:
			break;
	}
}