#include "RunningState.hpp"

RunningState::RunningState(sf::RenderWindow &window)
	: window(window)
{
	for (std::uint32_t i = 0; i < 2048; i++)
	{
		CelestialBody *body = new CelestialBody();
		body->SetMass(std::rand() % 2001 + 10);
		body->SetPosition(sf::Vector2f(std::rand() % 10'001 - 5000, std::rand() % 10'001 - 5000));
		body->SetRadius(body->GetMass() / 100.0f);
		body->SetVelocity(sf::Vector2f(std::rand() % 101 - 50, std::rand() % 101 - 50));
		body->SetPathVisible(true);
		body->SetPathLength(2048.0f);

		const sf::Color color(std::rand() % 201 + 55, std::rand() % 201 + 55, std::rand() % 201 + 55);
		body->SetBodyColor(color);
		body->SetPathColor(color);

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

	sf::CircleShape shape;
	shape.setFillColor(sf::Color::Transparent);
	// shape.setOutlineColor(sf::Color(179, 217, 255));

	if (bodyToFollow)
	{
		shape.setPosition(bodyToFollow->GetPosition());
		shape.setRadius(bodyToFollow->GetRadius() * 1.1f);
		shape.setOutlineColor(bodyToFollow->GetBodyColor());
	}

	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setOutlineThickness(shape.getRadius() / 15.0f);
	window.draw(shape);
	
	if (CelestialBody *body = world.GetBodyAt(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		shape.setPosition(body->GetPosition());
		shape.setRadius(body->GetRadius() * 1.1f);
		shape.setOutlineColor(body->GetBodyColor());
	}

	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setOutlineThickness(shape.getRadius() / 15.0f);
	window.draw(shape);
}

void RunningState::UpdateView(const float deltaTime)
{
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

	// View following body
	if (bodyToFollow)
	{
		const sf::Vector2f direction = bodyToFollow->GetPosition() - view.getCenter();

		view.move(direction * cameraFollowSpeed * deltaTime);

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

		case sf::Event::MouseWheelScrolled:
		{
			const float zoomAmount{ 1.1f }; // zoom by 10%
			
			if (event.mouseWheelScroll.delta > 0)
			{
				view.zoom(1.f / zoomAmount);
			}
			else if (event.mouseWheelScroll.delta < 0)
			{
					view.zoom(zoomAmount);
			}
		} break;

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