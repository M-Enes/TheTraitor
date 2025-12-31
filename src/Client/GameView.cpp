#include "GameView.h"
#include <iostream>

namespace {
	std::vector<sf::Texture> loadTextures(const std::string& executableFolderPath) {
		std::vector<sf::Texture> textures;
		textures.reserve(10);
		for (int i = 1; i <= 10; ++i) {
			sf::Texture texture;
			if (texture.loadFromFile(
				executableFolderPath + "/assets/avatars/pixel" + std::to_string(i) + ".png")) {
				textures.push_back(std::move(texture));
			}
		}
		return textures;
	}
}

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window, std::string executableFolderPath) :
		window(window),
		font(executableFolderPath + "/assets/fonts/CascadiaMono.ttf"),
		avatarTextures(loadTextures(executableFolderPath)),
		menuPhase(window, font, avatarTextures),
		lobbyPhase(window, font, avatarTextures),
		discussionPhase(),
		actionPhase(window, font, avatarTextures, executableFolderPath),
		resolutionPhase(),
		gameoverPhase(window, font),
		winPhase(window, font)
	{
	}

	const ViewData& GameView::handleMenuInput(const InputData& inputData) {
		return menuPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleLobbyInput(const InputData& inputData) {
		return lobbyPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleDiscussionPhaseInput(const InputData& inputData) {
		return discussionPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleActionPhaseInput(const InputData& inputData) {
		return actionPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleResolutionPhaseInput(const InputData& inputData) {
		return resolutionPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleGameoverInput(const InputData& inputData) {
		return gameoverPhase.handleInput(inputData);
	}
	const ViewData& GameView::handleWinInput(const InputData& inputData) {
		return winPhase.handleInput(inputData);
	}

	void GameView::renderMenu() {
		// Menu phase doesn't use gamestate yet, passing default
		menuPhase.render(GameState(), -1); 
	}

	void GameView::renderLobby(const GameState& gameState, int localPlayerID) {
		lobbyPhase.render(gameState, localPlayerID);
	}

	void GameView::renderDiscussionPhase(const GameState& gameState, int localPlayerID) {
		discussionPhase.render(gameState, localPlayerID);
	}

	void GameView::renderActionPhase(const GameState& gameState, int localPlayerID, int elapsedTimeSeconds, int roundCounter) {
		actionPhase.render(gameState, localPlayerID, static_cast<float>(elapsedTimeSeconds), roundCounter);
	}

	void GameView::renderResolutionPhase(const GameState& gameState, int localPlayerID) {
		resolutionPhase.render(gameState, localPlayerID);
	}

	void GameView::renderGameover(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter) {
		gameoverPhase.render(gameState, localPlayerID, static_cast<float>(totalTimeSeconds), roundCounter);
	}

	void GameView::renderWin(const GameState& gameState, int localPlayerID, int totalTimeSeconds, int roundCounter) {
		winPhase.render(gameState, localPlayerID, static_cast<float>(totalTimeSeconds), roundCounter);
	}

}
