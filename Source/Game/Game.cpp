#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(1280, 720), windowTitle);

	state = new RunningState(window);

	// Load custom cursor image
	sf::Image cursorImg;
	cursorImg.loadFromFile("Resources/Images/Cursor16x16.png");

	// Create sf::Cursor from that image
	sf::Cursor cursor;
	cursor.loadFromPixels(cursorImg.getPixelsPtr(), cursorImg.getSize(), sf::Vector2u(1, 1));

	// Change the window cursor
	window.setMouseCursor(cursor);
}

void Game::Run()
{
	while (window.isOpen())
	{
		float speed = 1.0f;
		dt = deltaTime.restart().asSeconds();

		this->HandleEvents();

		window.clear();

		state->Update();
		state->Render();

		window.display();

		this->UpdateWindowTitle();

		if (GameState *newState = state->NextState())
		{
			delete state;
			state = newState;
		}
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
