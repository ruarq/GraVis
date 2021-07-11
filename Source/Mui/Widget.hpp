#pragma once

#include <SFML/Graphics.hpp>

namespace Mui
{

class Context;

class Widget
{
public:
	enum class PositionType { Absolute, Relative };

public:
	virtual ~Widget() = default;

public:
	/**
	 * @brief IMPORTANT: Internal use only; Create the widget by providing the context it's part of.
	 */
	void Create(Context &context);

	/**
	 * @brief Destroy the widget
	 */
	virtual void Destroy() = 0;

	/**
	 * @brief Render the widget
	 */
	virtual void Render() = 0;

	/**
	 * @brief Updates the widget state based on the events provided to it's context;
	 * Only gets called if it's part of the events that it handles.
	 */
	virtual void OnEvent(const sf::Event &event) = 0;

	/**
	 * @brief Test wether a widget handles a certain event type or not
	 * @param eventType The type of event to test
	 * @return True if the widget handles the event type
	 */
	virtual bool HandlesEvent(const sf::Event::EventType eventType) = 0;

	/**
	 * @brief Set the position of the widget
	 * @param position The position of the widget
	 */
	void SetPosition(const sf::Vector2f &position);

	/**
	 * @brief Get the position of the widget
	 * @return The position of the widget
	 */
	sf::Vector2f GetPosition() const;

	/**
	 * @brief Set the relative position of the widget; x = 0 = left side of the window, x = 1 = right side of the window. Same goes for y 
	 * @param position The relative position of the widget
	 */
	void SetRelativePosition(const sf::Vector2f &position);

	/**
	 * @brief Get the relative position of the widget
	 * @return The relative position of the widget
	 */
	sf::Vector2f GetRelativePosition() const;

	/**
	 * @brief Set the size of the widget
	 * @param size The size of the widget
	 */
	void SetSize(const sf::Vector2f &size);

	/**
	 * @brief Get the size of the widget
	 * @return The size of the widget
	 */
	sf::Vector2f GetSize() const;

	/**
	 * @brief Set the relative size of the widget
	 * @param size The relative size of the widget
	 */
	void SetRelativeSize(const sf::Vector2f &size);

	/**
	 * @brief Get the relative size of the widget
	 * @return The relative size of the widget
	 */
	sf::Vector2f GetRelativeSize() const;

	/**
	 * @brief IMPORTANT: Internal use only; Obtain the position type a widget is currently using
	 * @return The position type the widget is currently using
	 */
	PositionType GetPositionType() const;

protected:
	Context *context;
	sf::Vector2f position, size;
	sf::Vector2f relativePosition, relativeSize; // for now we will have to use two vectors for each relative position and absolute position, same goes for size. TODO: Only use one vector for each size and pos

	PositionType positionType;
};

}
