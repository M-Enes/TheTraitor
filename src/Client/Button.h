#pragma once
#include <SFML/Graphics.hpp>

namespace TheTraitor {
	/**
	 * @brief UI Button class for user interaction.
	 */
	class Button {
	public:
		Button() = delete;

		/**
		 * @brief Constructor for Button.
		 * @param position Position of the button.
		 * @param size Size of the button.
		 * @param offset Offset for the text label.
		 * @param text The text to display on the button.
		 * @param font The font used for the text.
		 * @param window The render window reference.
		 * @param characterSize The size of the text characters.
		 * @param shapeFillColor The fill color of the button shape.
		 * @param shapeOutlineColor The outline color of the button shape.
		 * @param shapeOutlineThickness The thickness of the button outline.
		 * @param shapeHoverColor The color of the button when hovered.
		 * @param labelFillColor The fill color of the label text.
		 * @param labelOutlineColor The outline color of the label text.
		 */
		Button(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset,
			std::string text, const sf::Font& font, sf::RenderWindow& window,
			unsigned int characterSize = 24, sf::Color shapeFillColor = sf::Color::White, sf::Color shapeOutlineColor = sf::Color::White, float shapeOutlineThickness = 5, 
			sf::Color shapeHoverColor = sf::Color::White, sf::Color labelFillColor = sf::Color::Black, sf::Color labelOutlineColor = sf::Color::White);

		/**
		 * @brief Checks if the mouse is over the button.
		 * @param mousePosition The current mouse position.
		 * @return True if mouse is over the button, false otherwise.
		 */
		bool isMouseOver(sf::Vector2f mousePosition) const;

		/**
		 * @brief Updates the button's appearance based on hover state.
		 * @param isHovered True if the button is hovered, false otherwise.
		 */
		void updateHoverEffect(bool isHovered);

		/**
		 * @brief Renders the button to the window.
		 */
		void render();

		/**
		 * @brief Sets the outline color of the button shape.
		 * @param color The new outline color.
		 */
		void setShapeOutlineColor(sf::Color color);

		/**
		 * @brief Sets the fill color of the label text.
		 * @param color The new fill color.
		 */
		void setLabelFillColor(sf::Color color);

		/**
		 * @brief Sets the disabled state of the button.
		 * @param disabled True to disable, false to enable.
		 */
		void setDisabled(bool disabled);

		/**
		 * @brief Sets the text string of the button label.
		 * @param labelString The new text string.
		 */
		void setLabelString(std::string labelString);
	private:
		sf::RectangleShape shape;
		sf::Text label;
		sf::RenderWindow& window;
		sf::Color shapeFillColor;
		sf::Color shapeHoverColor;
		bool isDisabled = false;
	};
}