#include "InputHandler.h"
namespace TheTraitor {

	InputHandler::InputHandler(sf::RenderWindow& window) : window(window), inputData{ false, sf::Vector2i(0,0), false, ' '} {
	}

	void InputHandler::handleEvents() {
		inputData.isMouseClicked = false;
		inputData.mousePosition = sf::Mouse::getPosition(window);
		inputData.isKeyEntered = false;
		inputData.keyEntered = ' ';

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
			else if (const auto& keyEntered = event->getIf<sf::Event::TextEntered>()) {
				if (keyEntered->unicode < 128) {
					inputData.isKeyEntered = true;
					inputData.keyEntered = static_cast<char>(keyEntered->unicode);
				}
			}
		}
	}

	const InputData& InputHandler::getInputData() const {
		return inputData;
	}

	ActionPacket TheTraitor::InputHandler::prepareActionPacket() {
		return ActionPacket(); // TODO: return actual packet rather than default constructed one
	}

}