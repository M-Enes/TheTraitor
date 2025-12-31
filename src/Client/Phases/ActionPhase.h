#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <array>
#include <string>
#include <tuple>

namespace TheTraitor {

	class ActionPhase : public IGamePhase {
	public:
		ActionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath);

		void render(const GameState& gameState, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;
		ViewData viewData;

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
		
		std::array<sf::Text, 4> playerInfo;
		
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

		void resetViewData();
		bool isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point);
		void calculateCountries();
	};

}
