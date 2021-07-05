#pragma once

#include <SFML/Graphics.hpp>

class UI final
{
public:
	static void SetWindow(sf::RenderWindow *window);
	static sf::RenderWindow& GetWindow();

	static void BeginRender();
	static void EndRender();

private:
	static sf::RenderWindow *window;
	static sf::View uiView, prevView;
};