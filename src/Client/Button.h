#pragma once
#include <SFML/Graphics.hpp>

namespace TheTraitor {
	class Button {
	public:
		Button() = delete;
		Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset,
			std::string text, const sf::Font& font, sf::RenderWindow& window,
			unsigned int characterSize = 24, sf::Color shapeFillColor = sf::Color::White, sf::Color shapeOutlineColor = sf::Color::White, float shapeOutlineThickness = 5, 
			sf::Color shapeHoverColor = sf::Color::White, sf::Color labelFillColor = sf::Color::Black, sf::Color labelOutlineColor = sf::Color::White);
		bool isMouseOver(sf::Vector2f mousePosition) const;
		void updateHoverEffect(bool isHovered);
		void render();
		void setShapeOutlineColor(sf::Color color);
		void setLabelFillColor(sf::Color color);
	private:
		sf::RectangleShape shape;
		sf::Text label;
		sf::RenderWindow& window;
		sf::Color shapeFillColor;
		sf::Color shapeHoverColor;
	};
}