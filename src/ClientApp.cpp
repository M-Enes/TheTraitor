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
		const ViewData& viewData = gameView.handleInput(inputData);

		if (viewData.gotoState == GameState::LOBBY) {
			playerNames.push_back(viewData.enteredPlayerName);
			gameState = GameState::LOBBY;
		}
	}

	void ClientApp::updateLobby()
	{
		// TODO: Get actual player names from server
		sf::sleep(sf::seconds(1));
		gameState = GameState::PLAY;

	}

	void ClientApp::updatePlay() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleInput(inputData);
		if (viewData.isActionRequested) {
			// TODO: send action packet
		}
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
		case GameState::PLAY:
			updatePlay();
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
		case GameState::PLAY:
			gameView.renderPlay();
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

	ClientApp::ClientApp() :
		window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
		inputHandler(window),
		gameView(window),
		gameState(GameState::MENU)
	{
		window.setFramerateLimit(60);

		playerNames.push_back("Player 1");
		playerNames.push_back("Player 2");
		playerNames.push_back("Player 3");
		playerNames.push_back("Player 4");
	}

}