#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "BridgeTypes.h"
#include "ClientApp.h"
#include "Common/GameState.h"
#include "Common/PacketType.h"
#include <iostream>

namespace TheTraitor {

	ClientApp::ClientApp(std::string executableFolderPath)
		: window(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen),
		inputHandler(window),
		gameView(window, executableFolderPath),
		serverPort(53000),
		serverIp(sf::IpAddress::LocalHost),
		menuMusic(executableFolderPath + "/assets/music/enchantedtiki86.mp3"),
		actionPhaseMusic(executableFolderPath + "/assets/music/battleThemeB.mp3"),
		isConnected(false)
	{
		// TODO: add antialiasing option
		//windowSettings.antiAliasingLevel = 4;
		//window.create(sf::VideoMode::getFullscreenModes()[0], "The Traitor", sf::Style::None, sf::State::Fullscreen, windowSettings);

		gameState.currentPhase = MENU; // Test: Change to GAMEOVER or WIN to test end screens. Currently it is ACT
		menuMusic.play();

		window.setFramerateLimit(60);
	}

	void ClientApp::run() {
		sf::Clock clock;

		while (window.isOpen()) {
			sf::Time deltaTime = clock.restart();

			update(deltaTime);
			render();
			sendPackets();
			receivePackets();
		}
	}

	void ClientApp::updateMenu() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleMenuInput(inputData);

		if (viewData.gotoState == LOBBY) {
			gameState.currentPhase = LOBBY;
		}
	}

	void ClientApp::updateLobby() {
		// How can i check if the tcp socket is connected?
		if (!isConnected) {
			openTCPSocket(serverIp, serverPort);

			if (packetsToSend.size() > 0) {
				// Send name
				sf::Packet namePacket;
				PacketType namePacketType = PacketType::STRING;
				namePacket << namePacketType;
				namePacket << gameView.handleMenuInput(inputHandler.getInputData()).enteredPlayerName;
				packetsToSend.push_back(namePacket);

				// Send avatarID
				sf::Packet avatarPacket;
				PacketType avatarPacketType = PacketType::INT;
				avatarPacket << avatarPacketType;
				avatarPacket << gameView.handleMenuInput(inputHandler.getInputData()).avatarID;
				packetsToSend.push_back(avatarPacket);
			}

			for (int i = 0; i < packetsReceived.size(); ++i) {
				PacketType packetType;
				packetsReceived[i] >> packetType;
				if (packetType == PacketType::INT && !isIDReceived) {
					int tempID;
					packetsReceived[i] >> tempID;
					playerID = tempID;
					isIDReceived = true;
				}
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
			
			if (isIDReceived && packetsToSend.size() == 0) isConnected = true;
		}
		for (int i = 0; i < packetsReceived.size(); ++i) {
			PacketType packetType;
			packetsReceived[i] >> packetType;
			if (packetType == PacketType::GAMESTATE) {
				GameState newGameState;
				packetsReceived[i] >> newGameState;
				gameState = newGameState;
			}
			packetsReceived.erase(packetsReceived.begin() + i--);
		}
	}

	void ClientApp::updateDiscussionPhase() {
	}

	void ClientApp::updateActionPhase() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
		if (viewData.isActionRequested) {
			// TODO: send action packet
			ActionPacket actionPacket{ viewData.actionType, playerID, playerID }; // TODO: fill targetID correctly
			sendActionToServer(actionPacket);
		}
	}

	void ClientApp::updateResolutionPhase() {
		unsigned long int packetCount = 0;

		for (int i = 0; i < packetsReceived.size(); ++i) {
			PacketType packetType;
			packetsReceived[i] >> packetType;
			if (packetType == PacketType::ACTION_PACKET) packetCount++;
			else if (packetType == PacketType::GAMESTATE) {
				GameState newGameState;
				packetsReceived[i] >> newGameState;
				gameState = newGameState;
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
		}
		
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
			gameView.renderLobby(gameState);
			break;
		case DISCUSSION_PHASE:
			gameView.renderDiscussionPhase(gameState);
			break;
		case ACTION_PHASE:
			gameView.renderActionPhase(gameState);
			break;
		case RESOLUTION_PHASE:
			gameView.renderResolutionPhase(gameState);
			break;
		case GAMEOVER:
			gameView.renderGameover(gameState);
			break;
		case WIN:
			gameView.renderWin(gameState);
			break;
		case NONE:
			// Do nothing
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
		for (int i = 0; i < NUMBER_OF_RECEIVE_ATTEMPTS; ++i) {
			sf::Packet packet;
			sf::Socket::Status status = socket.receive(packet);
			if (status == sf::Socket::Status::Done) 
				packetsReceived.push_back(packet);
		}
	}

	void ClientApp::sendActionToServer(ActionPacket actionPacket) {
		sf::Packet packet;
		PacketType packetType = PacketType::ACTION_PACKET;
		packet << packetType;
		packet << actionPacket;
		packetsToSend.push_back(packet);
	}


	void ClientApp::sendPackets() {
		for (int i = 0; i < packetsToSend.size(); ++i) 
		if (socket.send(packetsToSend[i]) == sf::Socket::Status::Done) 
		packetsToSend.erase(packetsToSend.begin() + i--);
	}



} // namespace TheTraitor