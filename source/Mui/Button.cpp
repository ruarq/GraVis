#include "Button.hpp"

namespace Mui
{

void Button::Destroy()
{
}

void Button::Render()
{
	if (renderMode == RenderMode::Shape)
	{
		// update position and size
		shape.setPosition(position);
		shape.setSize(size);

		// draw
		context->GetTarget()->draw(shape);
		context->GetTarget()->draw(text);
	}
	else if (renderMode == RenderMode::Texture)
	{
		sf::Sprite sprite;
		sprite.setTexture(texture);
		sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
		context->GetTarget()->draw(sprite);
	}
}

void Button::OnEvent(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonReleased:
			if (sf::FloatRect(position, size).contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
			{
				this->onPress();
			}
			break;

		default:
			break;
	}
}

bool Button::HandlesEvent(const sf::Event::EventType eventType)
{
	switch (eventType)
	{
		case sf::Event::MouseButtonReleased:
			return true;

		default:
			return false;
	}
}

void Button::OnPress(const std::function<void()> &onPress)
{
	this->onPress = onPress;
}

void Button::SetColor(const sf::Color &color)
{
	shape.setFillColor(color);
	renderMode = RenderMode::Shape;
}

sf::Color Button::GetColor() const
{
	return shape.getFillColor();
}

void Button::SetTextColor(const sf::Color &color)
{
	text.setFillColor(color);
	renderMode = RenderMode::Shape;
}

sf::Color Button::GetTextColor() const
{
	return text.getFillColor();
}

void Button::SetTexture(const sf::Texture &texture)
{
	this->texture = texture;
	renderMode = RenderMode::Texture;
}

sf::Texture& Button::GetTexture()
{
	return texture;
}

}
