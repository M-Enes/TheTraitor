#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <string>

namespace TheTraitor {

	/**
	 * @brief Phase displayed when the game ends in a loss.
	 */
	class GameoverPhase : public IGamePhase {
	public:
		/**
		 * @brief Constructor for GameoverPhase.
		 * @param window The render window.
		 * @param font The font resource.
		 */
		GameoverPhase(sf::RenderWindow& window, sf::Font& font);

		/**
		 * @brief Renders the Game Over screen.
		 * @param gameState The current game state.
		 * @param localPlayerID The local player's ID.
		 * @param elapsedTime Total time played.
		 * @param roundCounter Total rounds played.
		 */
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;

		/**
		 * @brief Handles input for the Game Over screen (Quit).
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		ViewData viewData;
		
		sf::Text title;
		sf::Text totalRoundsLabel;
		sf::Text totalTimeLabel;
		sf::Text traitorInfoLabel;
		Button quitGameButton;

		void resetViewData();
	};

}
