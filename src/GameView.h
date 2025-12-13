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
		void renderLobby(const std::vector<std::string>& playerNames);
		void renderPlay();
		void renderGameover();
		void renderWin();
	private:
		sf::RenderWindow& window;
		ViewData viewData;
		sf::Font font;
		Button joinGameButton;
		sf::Text playerNameInputLabel;
		sf::Text playerNameInputTextBox;
		std::string playerNameInputTextBoxString;
		const int playerNameCharLimit = 20;
		std::array<sf::Text, 5> playerLabels;
	};
}