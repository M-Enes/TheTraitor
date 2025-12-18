#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "CommonTypes.h"
#include "ClientApp.h"

namespace TheTraitor {

	void ClientApp::run()
	{
		sf::Clock clock;

		while (window.isOpen()) {
			sf::Time deltaTime = clock.restart();

			update(deltaTime);
			render();
		}
	}

	void ClientApp::updateMenu() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleMenuInput(inputData);

		if (viewData.gotoState == GameState::LOBBY) {
			playerNames.push_back(viewData.enteredPlayerName);
			gameState = GameState::LOBBY;
		}
	}

	void ClientApp::updateLobby()
	{
		// TODO: Get actual player names from server
		sf::sleep(sf::seconds(1));
		gameState = GameState::ACTION_PHASE; // TODO: action set for debugging purposes

	}

	void ClientApp::updateDiscussionPhase()
	{
	}

	void ClientApp::updateActionPhase() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
		if (viewData.isActionRequested) {
			// TODO: send action packet
		}
	}

	void ClientApp::updateResolutionPhase()
	{
	}

	void ClientApp::updateGameover()
	{
	}

	void ClientApp::updateWin()
	{
	}

	void ClientApp::update(sf::Time deltaTime)
	{
		inputHandler.handleEvents();
		switch (gameState) {
		case GameState::MENU:
			updateMenu();
			break;
		case GameState::LOBBY:
			updateLobby();
			break;
		case GameState::DISCUSSION_PHASE:
			updateDiscussionPhase();
			break;
		case GameState::ACTION_PHASE:
			updateActionPhase();
			break;
		case GameState::RESOLUTION_PHASE:
			updateResolutionPhase();
			break;
		case GameState::GAMEOVER:
			updateGameover();
			break;
		case GameState::WIN:
			updateWin();
			break;
		}
	}

	void ClientApp::render()
	{

		window.clear(sf::Color(0, 0, 0, 255));
		switch (gameState) {
		case GameState::MENU:
			gameView.renderMenu();
			break;
		case GameState::LOBBY:
			gameView.renderLobby(playerNames); // Pass playerNames to renderLobby
			break;
		case GameState::DISCUSSION_PHASE:
			gameView.renderDiscussionPhase();
			break;
		case GameState::ACTION_PHASE:
			gameView.renderActionPhase();
			break;
		case GameState::RESOLUTION_PHASE:
			gameView.renderResolutionPhase();
			break;
		case GameState::GAMEOVER:
			gameView.renderGameover();
			break;
		case GameState::WIN:
			gameView.renderWin();
			break;
		}
		window.display();
	}

	ClientApp::ClientApp(std::string executableFolderPath) :
		window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
		inputHandler(window),
		gameView(window, executableFolderPath),
		serverPort(5000),//Give port here
		serverIp(sf::IpAddress::LocalHost),//Give ip here
		gameState(GameState::ACTION_PHASE) // currently action for testing purposes
	{
		window.setFramerateLimit(60);

		playerNames.push_back("Player 1");
		playerNames.push_back("Player 2");
		playerNames.push_back("Player 3");
		playerNames.push_back("Player 4");
	}

}