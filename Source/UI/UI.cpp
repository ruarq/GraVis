#include "UI.hpp"

sf::RenderWindow *UI::window = nullptr;
sf::View UI::uiView, UI::prevView;

void UI::SetWindow(sf::RenderWindow *window)
{
	UI::window = window;
}

sf::RenderWindow& UI::GetWindow()
{
	return *window;
}

void UI::BeginRender()
{
	prevView = window->getView();
	uiView = window->getDefaultView();
	uiView.setSize(window->getSize().x, window->getSize().y);
}

void UI::EndRender()
{
	window->setView(prevView);
}