#include "Button.h"

namespace TheTraitor {

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset,
		std::string text, const sf::Font& font, sf::RenderWindow& window,
		unsigned int characterSize, sf::Color shapeFillColor, sf::Color shapeOutlineColor, float shapeOutlineThickness,
		sf::Color labelFillColor, sf::Color labelOutlineColor) :
		shape(), label(font), window(window)
	{
		shape.setSize(size);
		shape.setPosition(position);
		shape.setFillColor(shapeFillColor);
		shape.setOutlineColor(shapeOutlineColor);
		shape.setOutlineThickness(shapeOutlineThickness);

		label.setString(text);
		label.setCharacterSize(characterSize);
		label.setPosition(position + offset);
		label.setFillColor(labelFillColor);
		label.setOutlineColor(labelOutlineColor);
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