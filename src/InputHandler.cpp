#include "InputHandler.h"
namespace TheTraitor {

	InputHandler::InputHandler(sf::RenderWindow& window) : window(window), inputData{ false, sf::Vector2i(0,0) }
	{
	}

	void InputHandler::handleEvents()
	{
		inputData.isMouseClicked = false;
		inputData.mousePosition = sf::Mouse::getPosition(window);

		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto& mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseEvent->button == sf::Mouse::Button::Left) {
					inputData.isMouseClicked = true;
					inputData.mousePosition = sf::Vector2i(mouseEvent->position);
				}
			}
		}
	}

	const InputData& InputHandler::getInputData() const
	{
		return inputData;
	}

}