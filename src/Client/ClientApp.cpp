#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "BridgeTypes.h"
#include "ClientApp.h"
#include "Common/GameState.h"
#include "Common/PacketType.h"

namespace TheTraitor {

	ClientApp::ClientApp(std::string executableFolderPath)
		: window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
		inputHandler(window),
		gameView(window, executableFolderPath),
		serverPort(5000),
		serverIp(sf::IpAddress::LocalHost),
		menuMusic(executableFolderPath + "/assets/music/enchantedtiki86.mp3"),
		actionPhaseMusic(executableFolderPath + "/assets/music/battleThemeB.mp3")
	{
		// TODO: add antialiasing option
		//windowSettings.antiAliasingLevel = 4;
		//window.create(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen, windowSettings);
		
		gameState.currentPhase = MENU; // Test: Change to GAMEOVER or WIN to test end screens. Currently it is ACT
		menuMusic.play();

		window.setFramerateLimit(60);

		// Dummy players for initial testing
		//gameState.players.push_back(Player("Player 1", new Country()));
		//gameState.players.push_back(Player("Player 2", new Country()));
		//gameState.players.push_back(Player("Player 3", new Country()));
		//gameState.players.push_back(Player("Player 4", new Country()));
		//gameState.players.push_back(Player("Player 5", new Country())); // for ui test
	}

	void ClientApp::run() {
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
	}

	void ClientApp::updateLobby() {
		receivePackets(); // Update the view regarding the updated game state

		sf::sleep(sf::seconds(1));
		menuMusic.stop();
		actionPhaseMusic.play();
	}

	void ClientApp::updateDiscussionPhase() {
	}

	void ClientApp::updateActionPhase() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
		if (viewData.isActionRequested) {
			// TODO: send action packet
			ActionPacket actionPacket; // TODO: fill actionPacket based on viewData
			sendActionToServer(actionPacket);
		}
	}

	void ClientApp::updateResolutionPhase() {
	}

	void ClientApp::updateGameover() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleGameoverInput(inputData);

		if (viewData.gotoState == NONE) {
			gameState.currentPhase = NONE;
			window.close(); // exit the game
		}
	}

	void ClientApp::updateWin() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleWinInput(inputData);

		if (viewData.gotoState == NONE) {
			gameState.currentPhase = NONE;
			window.close(); // exit the game
		}
	}

	void ClientApp::update(sf::Time deltaTime) {
		receivePackets();

		inputHandler.handleEvents();
		switch (gameState.currentPhase) {
		case MENU:
			updateMenu();
			break;
		case LOBBY:
			updateLobby();
			break;
		case DISCUSSION_PHASE:
			updateDiscussionPhase();
			break;
		case ACTION_PHASE:
			updateActionPhase();
			break;
		case RESOLUTION_PHASE:
			updateResolutionPhase();
			break;
		case GAMEOVER:
			updateGameover();
			break;
		case WIN:
			updateWin();
			break;
		default:
			break;
		}
	}

	void ClientApp::render() {
		window.clear(sf::Color(0, 0, 0, 255));
		switch (gameState.currentPhase) {
		case MENU:
			gameView.renderMenu();
			break;
		case LOBBY:
			gameView.renderLobby(gameState.players);
			break;
		case DISCUSSION_PHASE:
			gameView.renderDiscussionPhase();
			break;
		case ACTION_PHASE:
			gameView.renderActionPhase(gameState.players);
			break;
		case RESOLUTION_PHASE:
			gameView.renderResolutionPhase();
			break;
		case GAMEOVER:
			gameView.renderGameover();
			break;
		case WIN:
			gameView.renderWin();
			break;
		}

		window.display();
	}

	void ClientApp::openTCPSocket(sf::IpAddress ip, unsigned short port) {
		socket = sf::TcpSocket();
		if (socket.connect(ip, port) != sf::Socket::Status::Done) {
			//error
		}
		socket.setBlocking(false);
	}

	void ClientApp::receivePackets() {
		sf::Packet packet;
		PacketType packetType;
		if (socket.receive(packet) != sf::Socket::Status::Done) {
			//error
			return;
		}
		packet >> packetType;
		switch (packetType) {
			case PacketType::ACTION_PACKET: {
				// This case is not possible for client, but included for now
				ActionPacket actionPacket;
				packet >> actionPacket;
				// Process actionPacket
				break;
			} case PacketType::GAMESTATE: {
				GameState newGameState;
				packet >> newGameState;
				gameState = newGameState;
				break;
			} default:
				break;
		}
	}

	void ClientApp::sendActionToServer(ActionPacket actionPacket) {
		sf::Packet packet;
		PacketType packetType = PacketType::ACTION_PACKET;
		packet << packetType;
		packet << actionPacket;
		if (socket.send(packet) != sf::Socket::Status::Done) {
			//error
		}
	}



} // namespace TheTraitor