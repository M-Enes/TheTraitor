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
		const ViewData& handleMenuInput(const InputData& inputData);
		const ViewData& handleLobbyInput(const InputData& inputData);
		const ViewData& handleDiscussionPhaseInput(const InputData& inputData);
		const ViewData& handleActionPhaseInput(const InputData& inputData);
		const ViewData& handleResolutionPhaseInput(const InputData& inputData);
		void renderMenu();
		void renderLobby(const std::vector<std::string>& playerNames);
		void renderDiscussionPhase();
		void renderActionPhase();
		void renderResolutionPhase();
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
		const int playerNameCharLimit = 15;
		std::array<sf::Text, 5> playerLabels;
		sf::RectangleShape actionMenu;
		std::vector<std::pair<std::string, Button>> actionMenuButtons;
		sf::RectangleShape eventLogMenu;
		sf::Text roundLabel;
		sf::Text timerLabel;
		std::string eventLogString;
		sf::Text eventLogLabel;
		sf::VertexArray americaVertices;

		void resetViewData();
		bool isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point);
	};
}