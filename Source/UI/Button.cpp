#include "Button.hpp"

void Button::Render()
{
	UI::GetWindow().draw(sprite);
}

void Button::SetPosition(const sf::Vector2f &position)
{
	sprite.setPosition(position);
}

void Button::SetSize(const sf::Vector2f &size)
{
	sprite.setScale(size.x / float(texture.getSize().x), size.y / float(texture.getSize().y));
}

void Button::SetTexture(const sf::Texture &texture)
{
	this->texture = texture;
}

bool Button::IsPressed() const
{
	return sprite.getLocalBounds().contains(
		UI::GetWindow().mapPixelToCoords(
			sf::Mouse::getPosition(UI::GetWindow())));
}