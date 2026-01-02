#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <array>
#include <string>

namespace TheTraitor {

	/**
	 * @brief The main menu phase of the game.
	 */
	class MenuPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for MenuPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 * @param avatarTextures The avatar textures resource.
		 */
		MenuPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);
		
		/**
		 * @brief Renders the Main Menu UI (Title, Join Game, Avatar Selection).
		 * @param gameState The current game state.
		 * @param localPlayerID The local player's ID.
		 * @param elapsedTime Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Main Menu.
		 * @param inputData The raw input data.
		 * @return The resulting view data (Join Game request, etc.).
		 */
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		ViewData viewData;
		
		Button joinGameButton;
		sf::Text playerNameInputLabel;
		sf::Text playerNameInputTextBox;
		std::string playerNameInputTextBoxString;
		const unsigned long int playerNameCharLimit = 15;

		// Avatar UI
		sf::Text avatarLabel;
		std::vector<sf::Sprite> avatarSprites;
		int currentSelectedAvatarIndex;

		sf::Text titleLabel;
		sf::Text howToPlayLabel;

		void resetViewData();
		void initAvatarSprites(const std::vector<sf::Texture>& avatarTextures);

		sf::Clock blinkClock;
		bool showCursor;
	};

}
