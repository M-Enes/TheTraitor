#pragma once

#include <SFML/Graphics.hpp>
#include "ActionPacket.h"
#include "InputHandler.h"

namespace TheTraitor {
	
	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
	};

	class GameView
	{
	public:
		GameView(sf::RenderWindow& window);
		const ViewData& handleInput(const InputData& inputData);
		void render();
	private:
		sf::RenderWindow& window;
		ViewData viewData;
	};
}