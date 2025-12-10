#pragma once
#include <SFML/Graphics.hpp>

namespace TheTraitor {
	class Button {
	public:
		Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string text, const sf::Font& font, sf::RenderWindow& window);
		bool isMouseOver(sf::Vector2f mousePosition) const;
		void updateHoverEffect(bool isHovered);
		void render();
	private:
		sf::RectangleShape shape;
		sf::Text label;
		sf::RenderWindow& window;
	};
}