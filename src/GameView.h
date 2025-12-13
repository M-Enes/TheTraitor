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
		void renderLobby(int playerCount); // Modified to get playerCount
		void renderPlay();
		void renderGameover();
		void renderWin();
	private:
		sf::RenderWindow& window;
		ViewData viewData;
		sf::Font font;
		Button joinGameButton;
		sf::Text playerNameLabel;
		sf::Text playerNameTextBox;
		std::string playerNameTextBoxString;
		const int playerNameCharLimit = 20;
		sf::Texture mapTexture; // Texture for the game map
		sf::Sprite mapSprite; // Sprite to display the game map
	};
}