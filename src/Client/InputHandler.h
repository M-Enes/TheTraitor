#pragma once

#include <SFML/Graphics.hpp>
#include "Common/ActionPacket.h"
#include "BridgeTypes.h"

namespace TheTraitor {

	/**
	 * @brief Handles user input (keyboard and mouse) for the application.
	 */
	class InputHandler {
	public:
		/**
		 * @brief Constructor for InputHandler.
		 * @param window The render window to capture events from.
		 */
		InputHandler(sf::RenderWindow& window);

		/**
		 * @brief Processes input events from the window.
		 */
		void handleEvents();

		/**
		 * @brief Gets the latest input data.
		 * @return The InputData struct.
		 */
		const InputData& getInputData() const;
	private:
		sf::RenderWindow& window;
		InputData inputData;

	private:
		ActionPacket prepareActionPacket();
	};
}