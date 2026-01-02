#pragma once

#include "IGamePhase.h"
#include <vector>

namespace TheTraitor {

	/**
	 * @brief Phase where the results of the Action Phase are displayed.
	 */
	class ResolutionPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for ResolutionPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 * @param avatarTextures The avatar textures resource.
		 */
		ResolutionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);

		/**
		 * @brief Renders the Resolution Phase UI (Action results).
		 * @param gameState The current game state.
		 * @param localPlayerID The local player's ID.
		 * @param elapsedTime Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Resolution Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleInput(const InputData& inputData) override;

		/**
		 * @brief Sets the actions to process/display.
		 * @param actions The list of actions from the server.
		 */
		void setActions(const std::vector<ActionPacket>& actions);

	private:
		ViewData viewData;
		void resetViewData();

		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;
		std::vector<ActionPacket> actions;

		std::string getActionName(ActionType type);
	};

}
