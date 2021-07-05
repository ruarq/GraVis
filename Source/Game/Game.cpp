#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), windowTitle);
	UI::SetWindow(&window);

	state = new RunningState(window);
}

void Game::Run()
{
	while (window.isOpen())
	{
		float speed = 1.0f;
		dt = deltaTime.restart().asSeconds();

		this->HandleEvents();

		window.clear();

		if (GameState *newState = state->Update(dt))
		{
			delete state;
			state = newState;
		}

		state->Render();

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
				state->OnEvent(event);
				window.close();
				break;

			case sf::Event::Resized:
			{
				sf::View view = window.getView();
				view.setSize(event.size.width, event.size.height);
				window.setView(view);

				state->OnEvent(event);
			} break;

			default:
				state->OnEvent(event);
				break;
		}
	}
}
