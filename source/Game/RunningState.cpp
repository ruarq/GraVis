#include "RunningState.hpp"

RunningState::RunningState(sf::RenderWindow &window)
	: window(window)
{
	uiContext.Create(window);

	for (int i = 0; i < 1000; ++i)
	{
		auto body = new CelestialBody();
		body->SetPosition({ std::rand() % 20000, std::rand() % 20000 });
		body->SetMass((std::rand() % 901 + 100) * 10);
		body->SetRadius(std::rand() % 91 + 10);
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

	// temporary size controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		bodySize -= 100.0f * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		bodySize += 100.0f * deltaTime;
	}
	bodySize = std::abs(bodySize);

	return nullptr;
}

void RunningState::Render()
{
	window.setView(view);
	world.Render(window);

	/**
	 * Draw circle around selected celestial body and the body the mouse hovers on
	 */
	sf::CircleShape shape;
	shape.setFillColor(sf::Color::Transparent);

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

	/**
	 * Draw a circle where the mouse currently is, so the player can see how large the body will be
	 */
	shape.setRadius(bodySize);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	shape.setOutlineColor(sf::Color::White);
	shape.setOutlineThickness(1.5f);
	window.draw(shape);

	/**
	 * Draw a line when the mouse is dragged to show the direction the body will move in
	 */

	const sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (isDragging)
	{
		sf::VertexArray line(sf::PrimitiveType::LineStrip);
		line.append(window.mapPixelToCoords(mousePos));
		line.append(mouseDragStart);
		window.draw(line);
	}

	// Render ui
	uiContext.Render();
}

void RunningState::UpdateView(const float deltaTime)
{
	float cameraSpeed = 500.0f * currentZoom;

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
	uiContext.OnEvent(event);

	switch (event.type)
	{
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			view.zoom(currentZoom);
			break;

		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Button::Left:
					bodyToFollow = world.GetBodyAt(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

					if (!bodyToFollow)
					{
						isDragging = true;
						mouseDragStart = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					}
					break;

				default:
					break;
			}
			break;

		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Button::Left:
				{	
					if (isDragging)
					{
						isDragging = false;
						const sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

						CelestialBody *body = new CelestialBody();
						body->SetPosition(mouseDragStart);
						body->SetVelocity(mousePos - mouseDragStart);
						body->SetRadius(bodySize);
						body->SetMass(bodySize * 10'000.0f);
						body->SetPathVisible(true);
						world.AddBody(body);
					}
				}	break;

				default:
					break;
			}
			break;

		case sf::Event::MouseWheelScrolled:
		{
			const float zoomAmount = 1.1f; // zoom by 10%
			
			if (event.mouseWheelScroll.delta > 0)
			{
				view.zoom(1.f / zoomAmount);
				currentZoom *= 1.0f / zoomAmount;
			}
			else if (event.mouseWheelScroll.delta < 0)
			{
				view.zoom(zoomAmount);
				currentZoom *= zoomAmount;
			}
		}	break;

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