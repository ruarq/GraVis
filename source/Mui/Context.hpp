#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Widget.hpp"

namespace Mui
{

class Context final
{
public:
	/**
	 * @brief Default constructor
	 */
	Context() = default;

	/**
	 * @brief Create a context by providing a render target
	 */
	Context(sf::RenderTarget &target);

	/**
	 * @brief Destructor; calls Mui::Context::Destroy();
	 */
	~Context();

public:
	/**
	 * @brief Create the context by providing a render target
	 */
	void Create(sf::RenderTarget &target);

	/**
	 * @brief Destroy the context, this will reset it to it's default state.
	 */
	void Destroy();

	/**
	 * @brief Render every widget part of the context
	 */
	void Render();

	/**
	 * @brief Add a widget to the context
	 */
	void Add(Widget *widget);

	/**
	 * @brief On event function. To function properly, this function needs to receive every event,
	 * so it should be called in the sf::RenderWindow::pollEvent loop.
	 */
	void OnEvent(const sf::Event &event);

	/**
	 * @brief Get the render target of the context.
	 * @return Pointer to render target, or nullptr if no render target was specified
	 */
	sf::RenderTarget* GetTarget() const;

private:
	sf::RenderTarget *target = nullptr;
	sf::View view;

	std::vector<Widget*> widgets;
};

}