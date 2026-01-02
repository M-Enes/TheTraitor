#pragma once

#include "Client/BridgeTypes.h"
#include "Common/GameState.h"
#include <SFML/Graphics.hpp>

namespace TheTraitor {

	/**
	 * @brief Interface for game phases.
	 * 
	 * Defines methods for rendering and handling input for different game states.
	 */
	class IGamePhase {
	public:
		/**
		 * @brief Virtual destructor.
		 */
		virtual ~IGamePhase() = default;

		/**
		 * @brief Renders the phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param elapsedTime Time elapsed in the current phase or round.
		 * @param roundCounter The current round number.
		 */
		virtual void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) = 0;

		/**
		 * @brief Handles input for the phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		virtual const ViewData& handleInput(const InputData& inputData) = 0;
	};

}
