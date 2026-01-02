#include "Button.h"

namespace TheTraitor {

	Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset,
		std::string text, const sf::Font& font, sf::RenderWindow& window,
		unsigned int characterSize, sf::Color shapeFillColor, sf::Color shapeOutlineColor, float shapeOutlineThickness,
		sf::Color shapeHoverColor, sf::Color labelFillColor, sf::Color labelOutlineColor) :
		shape(), label(font), window(window), shapeFillColor(shapeFillColor), shapeHoverColor(shapeHoverColor)
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
		if (isDisabled) return;

		if (isHovered) {
			shape.setFillColor(shapeHoverColor);
		}
		else {
			shape.setFillColor(shapeFillColor);
		}
	}

	void Button::setDisabled(bool disabled) {
		if (isDisabled == disabled) return;
		isDisabled = disabled;
		if (isDisabled) {
			sf::Color fill = shape.getFillColor();
			fill.a = 100;
			shape.setFillColor(fill);
			
			sf::Color outline = shape.getOutlineColor();
			outline.a = 100;
			shape.setOutlineColor(outline);

			sf::Color textFill = label.getFillColor();
			textFill.a = 100;
			label.setFillColor(textFill);

			sf::Color textOutline = label.getOutlineColor();
			textOutline.a = 100;
			label.setOutlineColor(textOutline);
		} else {
			// Restore alpha
			sf::Color fill = shape.getFillColor();
			fill.a = 255;
			shape.setFillColor(fill);

			sf::Color outline = shape.getOutlineColor();
			outline.a = 255;
			shape.setOutlineColor(outline);
			
			sf::Color textFill = label.getFillColor();
			textFill.a = 255;
			label.setFillColor(textFill);
			
			sf::Color textOutline = label.getOutlineColor();
			textOutline.a = 255;
			label.setOutlineColor(textOutline);
			
			// Reset color to base to avoid stuck hover state
			shape.setFillColor(shapeFillColor);
		}
	}


	void Button::render() {
		window.draw(shape);
		window.draw(label);
	}

	void Button::setShapeOutlineColor(sf::Color color) {
		shape.setOutlineColor(color);
	}

	void Button::setLabelFillColor(sf::Color color) {
		label.setFillColor(color);
	}

	void Button::setLabelString(std::string labelString) {
		label.setString(labelString);
	}
}