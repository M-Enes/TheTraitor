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
		void drawMap();

		sf::RenderWindow& window;
		ViewData viewData;
		sf::Font font;
		Button joinGameButton;
		sf::Text playerNameInputLabel;
		sf::Text playerNameInputTextBox;
		std::string playerNameInputTextBoxString;
		const int playerNameCharLimit = 20;
		sf::Texture mapTexture; // Texture for the game map
		sf::Sprite mapSprite; // Sprite to display the game map
		std::array<sf::Text, 5> playerLabels;
<<<<<<< Updated upstream
=======
		sf::RectangleShape actionMenu;
		std::vector<std::pair<std::string, Button>> actionMenuButtons;
		sf::RectangleShape eventLogMenu;
		sf::Text roundLabel;
		sf::Text timerLabel;
		std::string eventLogString;
		sf::Text eventLogLabel;
		sf::VertexArray americaVertices;
		sf::VertexArray africaVertices;
		sf::VertexArray asiaVertices;
		sf::VertexArray australiaVertices;

		void resetViewData();
		bool isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point);
>>>>>>> Stashed changes
	};
}