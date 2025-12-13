#pragma once

#include <SFML/Graphics.hpp>
#include "ActionPacket.h"
#include "CommonTypes.h"
#include "Button.h"

namespace TheTraitor {

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
		void setPlayerCount(int count); //newly added function
	private:
		sf::RenderWindow& window;
		ViewData viewData;
		int playerCount = 0; //newly added member variable
		sf::Font font;
		Button joinGameButton;
		sf::Text playerNameLabel;
		sf::Text playerNameTextBox;
		std::string playerNameTextBoxString;
		const int playerNameCharLimit = 20;
	};
}