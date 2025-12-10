#include "Button.h"

namespace TheTraitor {

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string text, const sf::Font& font, sf::RenderWindow& window) :
		shape(), label(font), window(window)
	{
		shape.setSize(size);
		shape.setPosition(position);
		shape.setFillColor(sf::Color::White);

		label.setString(text);
		label.setCharacterSize(24);
		label.setPosition(position + offset);
		label.setFillColor(sf::Color::Black);
	}

	bool Button::isMouseOver(sf::Vector2f mousePosition) const
	{
		if (shape.getGlobalBounds().contains(mousePosition)) {
			return true;
		}
		return false;
	}

	void Button::updateHoverEffect(bool isHovered)
	{
		if (isHovered) {
			shape.setFillColor(sf::Color(200, 200, 200));
		}
		else {
			shape.setFillColor(sf::Color(sf::Color::White));
		}
	}

	void Button::render() {
		window.draw(shape);
		window.draw(label);
	}
}