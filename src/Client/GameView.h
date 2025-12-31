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

	class GameView
	{
	public:
		GameView(sf::RenderWindow& window, std::string executableFolderPath);
		const ViewData& handleMenuInput(const InputData& inputData);
		const ViewData& handleLobbyInput(const InputData& inputData);
		const ViewData& handleDiscussionPhaseInput(const InputData& inputData);
		const ViewData& handleActionPhaseInput(const InputData& inputData);
		const ViewData& handleResolutionPhaseInput(const InputData& inputData);
		const ViewData& handleGameoverInput(const InputData& inputData);
		const ViewData& handleWinInput(const InputData& inputData);
		
		void renderMenu();
		void renderLobby(const GameState& gameState, int localPlayerID);
		void renderDiscussionPhase(const GameState& gameState, int localPlayerID);
		void renderActionPhase(const GameState& gameState, int localPlayerID, int elapsedTimeSeconds, int roundCounter);
		void renderResolutionPhase(const GameState& gameState, int localPlayerID);
		void renderGameover(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter);
		void renderWin(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter);
		
		const ViewData& getViewData(); // Needed? ClientApp doesn't seem to use it except via return values of handlers.
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