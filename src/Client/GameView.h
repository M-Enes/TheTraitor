#pragma once

#include <SFML/Graphics.hpp>
#include "Common/ActionPacket.h"
#include "BridgeTypes.h"
#include "Button.h"
#include <vector>
#include "Common/Player.h"

namespace TheTraitor {

	class GameView
	{
	public:
		GameView(sf::RenderWindow& window, std::string executableFolderPath);
		const ViewData& handleMenuInput(const InputData& inputData);
		const ViewData& handleLobbyInput(const InputData& inputData);
		const ViewData& handleDiscussionPhaseInput(const InputData& inputData);
		const ViewData& handleActionPhaseInput(const InputData& inputData);
		const ViewData& handleResolutionPhaseInput(const InputData& inputData);
		const ViewData& handleGameoverInput(const InputData& inputData);
		const ViewData& handleWinInput(const InputData& inputData);
		void renderMenu();
		void renderLobby(const GameState& gameState);
		void renderDiscussionPhase(const GameState& gameState);
		void renderActionPhase(const GameState& gameState);
		void renderResolutionPhase(const GameState& gameState);
		void renderGameover(const GameState& gameState);
		void renderWin(const GameState& gameState);
		const ViewData& getViewData();
	private:
		sf::RenderWindow& window;
		ViewData viewData;
		sf::Font font;
		Button joinGameButton;
		sf::Text playerNameInputLabel;
		sf::Text playerNameInputTextBox;
		std::string playerNameInputTextBoxString;
		const int playerNameCharLimit = 15;
		std::array<sf::Text, 5> playerLabels;
		sf::RectangleShape actionMenu;
		std::vector<std::tuple<std::string, Button, ActionType>> actionMenuButtons;
		sf::RectangleShape eventLogMenu;
		std::string eventLogString;
		sf::Text eventLogMenuLabel;
		sf::Text eventLogLabel;
		sf::RectangleShape infoMenu;
		sf::RectangleShape topBar;
		sf::Text roundLabel;
		sf::Text phaseLabel;
		sf::Text timerLabel;
		sf::VertexArray americaVertices;
		sf::VertexArray africaVertices;
		sf::VertexArray asiaVertices;
		sf::VertexArray australiaVertices;
		sf::VertexArray europeVertices;
		std::array<std::pair<const std::vector<sf::Vector2f>*, sf::VertexArray*>, 5> allCountries;
		std::array<std::array<sf::Text, 4>, 5> playerInfo;
		sf::Texture economyIconTexture;
		sf::Texture healthIconTexture;
		sf::Texture educationIconTexture;
		sf::Sprite economyIconSprite;
		sf::Sprite healthIconSprite;
		sf::Sprite educationIconSprite;
		sf::Color countryNormalColor;
		sf::Color countryHoverColor;
		sf::Color countrySelectedColor;
		sf::Vector2f countriesOffset;

		// Gameover and Win screen elements
		sf::Text gameoverTitle;
		sf::Text winTitle;
		sf::Text totalRoundsLabel;
		sf::Text totalTimeLabel;
		Button quitGameButton;

		void resetViewData();
		bool isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point);
		void calculateCountries();
	};
}