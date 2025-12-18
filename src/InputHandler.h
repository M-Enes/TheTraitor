#pragma once

#include <SFML/Graphics.hpp>
#include "ActionPacket.h"
#include "CommonTypes.h"

namespace TheTraitor {

	class InputHandler {
	public:
		InputHandler(sf::RenderWindow& window);
		void handleEvents();
		const InputData& getInputData() const;
	private:
		sf::RenderWindow& window;
		InputData inputData;

	private:
		ActionPacket prepareActionPacket();
	};
}