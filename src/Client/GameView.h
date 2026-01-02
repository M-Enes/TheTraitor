#pragma once

#include <SFML/Graphics.hpp>
#include "Common/ActionPacket.h"
#include "BridgeTypes.h"
#include <vector>
#include "Common/Player.h"

#include "Client/Phases/MenuPhase.h"
#include "Client/Phases/LobbyPhase.h"
#include "Client/Phases/DiscussionPhase.h"
#include "Client/Phases/ActionPhase.h"
#include "Client/Phases/ResolutionPhase.h"
#include "Client/Phases/GameoverPhase.h"
#include "Client/Phases/WinPhase.h"

namespace TheTraitor {

	/**
	 * @brief Class responsible for rendering the game and handling UI interactions.
	 */
	class GameView
	{
	public:
		/**
		 * @brief Constructor for GameView.
		 * @param window The render window.
		 * @param executableFolderPath Path to the executable, for resource loading.
		 */
		GameView(sf::RenderWindow& window, std::string executableFolderPath);

		/**
		 * @brief Handles input during the Menu Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data (actions/state changes).
		 */
		const ViewData& handleMenuInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Lobby Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleLobbyInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Discussion Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleDiscussionPhaseInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Action Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleActionPhaseInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Resolution Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleResolutionPhaseInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Gameover Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleGameoverInput(const InputData& inputData);

		/**
		 * @brief Handles input during the Win Phase.
		 * @param inputData The raw input data.
		 * @return The resulting view data.
		 */
		const ViewData& handleWinInput(const InputData& inputData);
		
		/**
		 * @brief Renders the Menu Phase.
		 */
		void renderMenu();

		/**
		 * @brief Renders the Lobby Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 */
		void renderLobby(const GameState& gameState, int localPlayerID);

		/**
		 * @brief Renders the Discussion Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param elapsedTimeSeconds Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void renderDiscussionPhase(const GameState& gameState, int localPlayerID, int elapsedTimeSeconds, int roundCounter);

		/**
		 * @brief Renders the Action Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param elapsedTimeSeconds Time elapsed in the phase.
		 * @param roundCounter Current round number.
		 */
		void renderActionPhase(const GameState& gameState, int localPlayerID, int elapsedTimeSeconds, int roundCounter);

		/**
		 * @brief Renders the Resolution Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 */
		void renderResolutionPhase(const GameState& gameState, int localPlayerID);

		/**
		 * @brief Sets the actions to be displayed in the Resolution Phase.
		 * @param actions Vector of action packets.
		 */
		void setResolutionActions(const std::vector<ActionPacket>& actions);

		/**
		 * @brief Renders the Gameover Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param totalTimeSeconds Total game time.
		 * @param roundCounter Total rounds played.
		 */
		void renderGameover(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter);

		/**
		 * @brief Renders the Win Phase.
		 * @param gameState The current game state.
		 * @param localPlayerID The ID of the local player.
		 * @param totalTimeSeconds Total game time.
		 * @param roundCounter Total rounds played.
		 */
		void renderWin(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter);
		
		/**
		 * @brief Gets the current view data.
		 * @return The view data struct.
		 */
		const ViewData& getViewData(); 
	private:
		sf::RenderWindow& window;
		sf::Font font;
		
		// Resources shared with phases
		std::vector<sf::Texture> avatarTextures;

		// Phases
		MenuPhase menuPhase;
		LobbyPhase lobbyPhase;
		DiscussionPhase discussionPhase;
		ActionPhase actionPhase;
		ResolutionPhase resolutionPhase;
		GameoverPhase gameoverPhase;
		WinPhase winPhase;
	};
}