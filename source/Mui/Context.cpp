#include "Context.hpp"

namespace Mui
{

Context::Context(sf::RenderTarget &target)
{
	this->Create(target);
}

Context::~Context()
{
	this->Destroy();
}

void Context::Create(sf::RenderTarget &target)
{
	this->target = &target;
	view = target.getDefaultView();
	view.setSize(sf::Vector2f(target.getSize()));
}

void Context::Destroy()
{
	for (Widget *widget : widgets)
	{
		widget->Destroy();
		delete widget;
	}

	widgets.clear();
}

void Context::Render()
{
	const sf::View prevView = target->getView();
	target->setView(view);

	for (Widget *widget : widgets)
	{
		widget->Render();
	}

	target->setView(prevView);
}

void Context::Add(Widget *widget)
{
	widget->Create(*this);
	widgets.push_back(widget);
}

void Context::OnEvent(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			view.setCenter(view.getSize() / 2.0f);
			break;

		default:
			break;
	}

	for (Widget *widget : widgets)
	{
		if (widget->HandlesEvent(event.type))
		{
			widget->OnEvent(event);
		}
	}
}

sf::RenderTarget* Context::GetTarget() const
{
	return target;
}

}