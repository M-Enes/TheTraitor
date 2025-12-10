#pragma once

#include <SFML/Graphics.hpp>
#include "ActionPacket.h"

namespace TheTraitor {

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
	};

	class InputHandler {
	public:
		InputHandler(sf::RenderWindow& window);
		void handleEvents();
		const InputData& getInputData() const;
	private:
		sf::RenderWindow& window;
		InputData inputData;
	};
}