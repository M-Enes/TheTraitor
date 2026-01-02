#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace TheTraitor {

	/**
	 * @brief Phase for player discussion before the Action Phase.
	 */
	class DiscussionPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for DiscussionPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 * @param avatarTextures The avatar textures resource.
		 * @param executableFolderPath Path to usage resources.
		 */
		DiscussionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath);

		/**
		 * @brief Renders the Discussion Phase UI.
		 * @param gameState The current game state.
		 * @param localPlayerID The local player's ID.
		 * @param elapsedTime Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Discussion Phase (Ready button).
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		ViewData viewData;
		void resetViewData();

		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;

		Button readyButton;
		bool isReady;

		// UI Elements
		sf::Text titleLabel;
		sf::Text timerLabel;
		
		// Player Info Elements (Reused logic from ActionPhase)
		struct PlayerInfoUI {
			sf::Text name;
			sf::Text economy;
			sf::Text health;
			sf::Text education;
		} playerInfo;


		sf::Texture economyIconTexture;
		sf::Texture healthIconTexture;
		sf::Texture educationIconTexture;

		sf::Sprite economyIconSprite;
		sf::Sprite healthIconSprite;
		sf::Sprite educationIconSprite;

		sf::Color countryNormalColor;
		sf::Color countryHoverColor; // Not used for map interaction here but maybe for highlighting?
		sf::Color countrySelectedColor;
		
		int currentRound = 0;
	};

}
