#pragma once

#include "Client/Phases/IGamePhase.h"
#include <vector>
#include <array>
#include <string>

namespace TheTraitor {

	/**
	 * @brief Phase where players wait for the game to start.
	 */
	class LobbyPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for LobbyPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 * @param avatarTextures The avatar textures resource.
		 */
		LobbyPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);

		/**
		 * @brief Renders the Lobby Phase UI (Player list).
		 * @param gameState The current game state.
		 * @param localPlayerID The local player's ID.
		 * @param elapsedTime Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Lobby Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;
		ViewData viewData;

		std::array<sf::Text, 5> playerLabels;

		void resetViewData();
	};

}
