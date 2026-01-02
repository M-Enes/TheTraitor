#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <array>
#include <string>
#include <tuple>
#include <map>

namespace TheTraitor {

	/**
	 * @brief Phase where players perform actions (Attack, Trade, etc.).
	 */
	class ActionPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for ActionPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 * @param avatarTextures The avatar textures resource.
		 * @param executableFolderPath Path to usage resources.
		 */
		ActionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath);

		/**
		 * @brief Renders the Action Phase UI (Map, Buttons, Stats).
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param elapsedTime Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Action Phase (Selecting actions, targets).
		 * @param inputData The raw input data.
		 * @return The resulting view data with requested action.
		 */
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
		sf::Color countryDestroyedColor;
		sf::Vector2f countriesOffset;
		
		
		// Game Rules Tracking
		bool publicActionUsed = false;
		bool secretActionUsed = false;
		int currentRound = 0;
		
		// Cached State (Updated per render)
		int cachedLocalPlayerID = -1;
		bool cachedIsTraitor = false; 
		CountryType cachedLocalPlayerCountryType = CountryType::NONE;
		
		std::map<CountryType, bool> destroyedCountries;
		bool isLocalPlayerDestroyed = false;

		void markActionUsed(ActionType type);
		bool isActionAllowed(ActionType type) const;

		// Existing members
		bool isTraitor; // Keeping for existing render logic compatibility (will sync with cachedIsTraitor)
		ActionType hoveredAction;
		bool isActionHovered;

		struct ActionEffect {
			int playerEffect;
			int targetEffect;
			CountryStatType statType;
		};

		ActionEffect getPreviewEffects(ActionType type);

		void resetViewData();
		bool isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point);
		void calculateCountries();
		
		std::vector<ActionPacket> lastRoundActions;
		bool updateLogString = false;
	public:
		/**
		 * @brief Sets the event log actions from the previous round.
		 * @param actions The list of actions to display in the log.
		 */
		void setEventLog(const std::vector<ActionPacket>& actions);
	};

}
