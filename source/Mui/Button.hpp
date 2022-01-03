#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

#include "Context.hpp"
#include "Widget.hpp"

namespace Mui
{

class Button final : public Widget
{
private:
	enum class RenderMode { Shape, Texture };

public:
	/**
	 * @brief Destroy function; Needs to be implemented because of Mui::Widget
	 */
	void Destroy() override;

	/**
	 * @brief Render the button to the target of it's context
	 */
	void Render() override;

	/**
	 * @brief IMPORTANT: Internal use only; Updates the buttons state
	 */
	void OnEvent(const sf::Event &event) override;

	/**
	 * @brief Test wether the button handles a event or not
	 * @param eventType The type of the event
	 * @return True if the button handles that event
	 */
	bool HandlesEvent(const sf::Event::EventType eventType) override;

	/**
	 * @brief Set the on press function for the button. Gets called when the button is pressed
	 * @param onPress The on press function that gets called when the button is pressed
	 */
	void OnPress(const std::function<void()> &onPress);

	/**
	 * @brief Set the color of the button
	 * @param color The color of the button
	 */
	void SetColor(const sf::Color &color);

	/**
	 * @brief Get the color of the button
	 * @return The color of the button (default: white)
	 */
	sf::Color GetColor() const;

	/**
	 * @brief Set the text color of the button
	 * @param color The text color of the button
	 */
	void SetTextColor(const sf::Color &color);

	/**
	 * @brief Get the text color of the button
	 * @return The text color of the button (default: black)
	 */
	sf::Color GetTextColor() const;

	/**
	 * @brief Set the texture for the button
	 * @param texture The texture for the button
	 */
	void SetTexture(const sf::Texture &texture);

	/**
	 * @brief Get a ref to the texture of the button
	 * @return Reference to the texture of the button
	 */
	sf::Texture& GetTexture();

private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Texture texture;

	RenderMode renderMode = RenderMode::Shape;

	std::function<void()> onPress = nullptr;
};

}