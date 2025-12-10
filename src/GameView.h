#pragma once

#include <SFML/Graphics.hpp>
#include "ActionPacket.h"
#include "InputHandler.h"
#include "GameState.h"
#include "Button.h"

namespace TheTraitor {
	
	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		GameState gotoState;
	};

	class GameView
	{
	public:
		GameView(sf::RenderWindow& window);
		const ViewData& handleInput(const InputData& inputData);
		void renderMenu();
		void renderLobby();
		void renderPlay();
		void renderGameover();
		void renderWin();
	private:
		sf::RenderWindow& window;
		ViewData viewData;
		sf::Font font;
		Button joinGameButton;
	};
}