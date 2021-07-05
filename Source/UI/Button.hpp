#pragma once

#include <SFML/Graphics.hpp>

#include "UI.hpp"

class Button final
{
public:
	void Render();
	
	void SetPosition(const sf::Vector2f &position);
	void SetSize(const sf::Vector2f &size);

	void SetTexture(const sf::Texture &texture);

	bool IsPressed() const;

private:
	sf::Texture texture;
	sf::Sprite sprite;
};