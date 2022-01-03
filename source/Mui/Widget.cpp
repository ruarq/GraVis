#include "Widget.hpp"

namespace Mui
{

void Widget::Create(Context &context)
{
	this->context = &context;
}

void Widget::SetPosition(const sf::Vector2f &position)
{
	this->position = position;
}

sf::Vector2f Widget::GetPosition() const
{
	return position;
}

void Widget::SetRelativePosition(const sf::Vector2f &position)
{
	relativePosition = position;	
}

sf::Vector2f Widget::GetRelativePosition() const
{
	return relativePosition;
}

void Widget::SetSize(const sf::Vector2f &size)
{
	this->size = size;
}

sf::Vector2f Widget::GetSize() const
{
	return size;
}

void Widget::SetRelativeSize(const sf::Vector2f &size)
{
	relativeSize = size;
}

sf::Vector2f Widget::GetRelativeSize() const
{
	return relativeSize;
}

}
