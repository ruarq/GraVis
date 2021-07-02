#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(1280u, 720u), windowTitle);
}

void Game::Run()
{
	while (window.isOpen())
	{
		const float dt = deltaTime.restart().asSeconds();

		this->HandleEvents();

		window.clear();

		world.Update(dt);
		world.Render(window);

		window.display();

		this->UpdateWindowTitle(dt);
	}
}

void Game::UpdateWindowTitle(const float deltaTime)
{
	using namespace std::string_literals;

	if (windowTitleUpdate.getElapsedTime().asSeconds() >= 1.0f / windowTitleUpdateFreq)
	{
		window.setTitle(windowTitle + " - "s + std::to_string(int(1.0f / deltaTime)) + " FPS"s);
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

			default:
				break;
		}
	}
}