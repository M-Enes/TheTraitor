#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "BridgeTypes.h"
#include "ClientApp.h"
#include "Common/GameState.h"
#include "Common/PacketType.h"
#include "Common/Role.h"
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
		winMusic(executableFolderPath + "/assets/music/Victory1.mp3"),
		gameoverMusic(executableFolderPath + "/assets/music/NoHope.mp3"),
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
			openTCPSocket(serverIp, serverPort);
		}
	}

	void ClientApp::updateLobby() {
		// How can i check if the tcp socket is connected?
		if (!isConnected) {

			if (!isNameAndAvatarSent) {
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

				isNameAndAvatarSent = true;
			}

			for (int i = 0; i < packetsReceived.size(); ++i) {
				sf::Packet packet = packetsReceived[i];
				PacketType packetType;
				packet >> packetType;
				std::cout << static_cast<int>(packetType) << std::endl;
				if (packetType == PacketType::INT && !isIDReceived) {
					int tempID;
					packet >> tempID;
					playerID = tempID;
					isIDReceived = true;
					std::cout << "player id received and set to " << playerID << std::endl;
					packetsReceived.erase(packetsReceived.begin() + i--);
				}
			}

			if (isIDReceived && packetsToSend.size() == 0) isConnected = true;
		}
		else {

			for (int i = 0; i < packetsReceived.size(); ++i) {
				sf::Packet packet = packetsReceived[i];
				PacketType packetType;
				packet >> packetType;
				std::cout << "gamestate receiving loop " << static_cast<int>(packetType) << std::endl;
				if (packetType == PacketType::GAMESTATE) {
					GameState newGameState;
					packet >> newGameState;
					gameState = newGameState;
					if (newGameState.currentPhase == ACTION_PHASE) {
						menuMusic.stop();
						actionPhaseMusic.play();
						totalTimer.restart();
						phaseTimer.restart();
					}
				}
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
		}
	}

	void ClientApp::updateDiscussionPhase() {
	}

	void ClientApp::updateActionPhase() {
		const InputData& inputData = inputHandler.getInputData();
		const ViewData& viewData = gameView.handleActionPhaseInput(inputData);
		if (viewData.isActionRequested) {
			if (static_cast<int>(viewData.actionTargetCountryType) != -1) {
				int actionTargetPlayerID = -1;
				for (const auto& player : gameState.players) {
					if (player.getCountry()->getType() == static_cast<CountryType>(viewData.actionTargetCountryType)) {
						actionTargetPlayerID = player.getPlayerID();
						break;
					}
				}
				
				// Action is already validated by ActionPhase::handleInput
				ActionPacket actionPacket{ viewData.actionType, playerID, actionTargetPlayerID };
				sendActionToServer(actionPacket);
			}
		}

		for (int i = 0; i < packetsReceived.size(); ++i) {
			sf::Packet packet = packetsReceived[i];
			PacketType packetType;
			packet >> packetType;
			std::cout << "action phase gamestate receiving loop " << static_cast<int>(packetType) << std::endl;
			if (packetType == PacketType::GAMESTATE) {
				GameState newGameState;
				packet >> newGameState;
				Role* role;
				for (const auto& player : newGameState.players) {
					if (player.getPlayerID() == playerID) {
						std::cout << "player found" << std::endl;
						role = player.getRole();
					}
				}
				if (role->getName() == "Traitor") {
					if (newGameState.currentPhase == WIN) {
						newGameState.currentPhase = GAMEOVER;
					}
					else if (newGameState.currentPhase == GAMEOVER) {
						newGameState.currentPhase = WIN;
					}
				}
				gameState = newGameState;
				actionPhaseMusic.stop();
				totalTimer.stop();
				if (newGameState.currentPhase == WIN) {
					winMusic.play();
				}
				else if (newGameState.currentPhase == GAMEOVER) {
					gameoverMusic.play();
				}

				// If phase changed, break to process state transition properly (e.g. to ResolutionPhase)
				// without consuming subsequent packets meant for the new phase.
				if (gameState.currentPhase != ACTION_PHASE) {
					packetsReceived.erase(packetsReceived.begin() + i);
					return;
				}
			}
			packetsReceived.erase(packetsReceived.begin() + i--);
		}
	}

	void ClientApp::updateResolutionPhase() {
		// std::cout << "Updating Resolution Phase..." << std::endl; // Too verbose for every frame
		for (int i = 0; i < packetsReceived.size(); ++i) {
			sf::Packet& packet = packetsReceived[i];
			
			sf::Packet packetCopy = packet;
			PacketType packetType;
			if (!(packetCopy >> packetType)) {
				std::cout << "ResolutionPhase: Invalid packet received, discarding." << std::endl;
				packetsReceived.erase(packetsReceived.begin() + i--);
				continue;
			}

			if (packetType == PacketType::INT) {
				if (expectedResolutionActionCount == -1) {
					int count;
					packetCopy >> count;
					expectedResolutionActionCount = count;
					resolutionActions.clear();
					std::cout << "ResolutionPhase: Received Action Count = " << count << std::endl;
					packetsReceived.erase(packetsReceived.begin() + i--);
				}
				else {
					std::cout << "ResolutionPhase: Ignored extra INT packet." << std::endl;
					packetsReceived.erase(packetsReceived.begin() + i--);
				}
			}
			else if (packetType == PacketType::ACTION_PACKET) {
				ActionPacket ap;
				packetCopy >> ap;
				resolutionActions.push_back(ap);
				std::cout << "ResolutionPhase: Received ActionPacket. Total collected: " << resolutionActions.size() << "/" << expectedResolutionActionCount << std::endl;
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
			else if (packetType == PacketType::GAMESTATE) {
				GameState newGameState;
				packetCopy >> newGameState;
				
				pendingGameState = newGameState;
				hasPendingGameState = true;
				std::cout << "ResolutionPhase: Received pending GameState. Next Phase: " << (int)newGameState.currentPhase << std::endl;
				
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
			else {
				std::cout << "ResolutionPhase: Unknown packet type " << (int)packetType << " received." << std::endl;
				packetsReceived.erase(packetsReceived.begin() + i--);
			}
		}

		if (expectedResolutionActionCount != -1 && resolutionActions.size() >= expectedResolutionActionCount) {
			if (!resolutionActionsReceived) {
				std::cout << "ResolutionPhase: All actions received (" << resolutionActions.size() << "). Starting timer." << std::endl;
				gameView.setResolutionActions(resolutionActions);
				resolutionActionsReceived = true;
				phaseTimer.restart(); 
				resolutionTimerStarted = true;
			}
		}

		if (resolutionTimerStarted) {
			float elapsed = phaseTimer.getElapsedTime().asSeconds();
			// std::cout << "Resolution Timer: " << elapsed << "/10.0" << std::endl; 
			if (elapsed >= 10.0f) {
				std::cout << "ResolutionPhase: Timer finished." << std::endl;
				if (hasPendingGameState) {
					std::cout << "ResolutionPhase: Applying pending GameState." << std::endl;
					gameState = pendingGameState;
					
					expectedResolutionActionCount = -1;
					resolutionActions.clear();
					resolutionActionsReceived = false;
					hasPendingGameState = false;
					resolutionTimerStarted = false;
					
					if (gameState.currentPhase == ACTION_PHASE) { 
						// This branch seems odd if next phase is usually Discussion which leads to Action? 
						// But if we go back to Action directly:
						menuMusic.stop();
						actionPhaseMusic.play();
						totalTimer.restart(); 
						phaseTimer.restart();
					}
				} else {
					// std::cout << "ResolutionPhase: Timer done but no pending GameState." << std::endl;
				}
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
			gameView.renderLobby(gameState, playerID);
			break;
		case DISCUSSION_PHASE:
			gameView.renderDiscussionPhase(gameState, playerID);
			break;
		case ACTION_PHASE:
			gameView.renderActionPhase(gameState, playerID, static_cast<int>(phaseTimer.getElapsedTime().asSeconds()), roundCounter);
			break;
		case RESOLUTION_PHASE:
			gameView.renderResolutionPhase(gameState, playerID);
			break;
		case GAMEOVER:
			gameView.renderGameover(gameState, playerID, static_cast<int>(totalTimer.getElapsedTime().asSeconds()), roundCounter);
			break;
		case WIN:
			gameView.renderWin(gameState, playerID, static_cast<int>(totalTimer.getElapsedTime().asSeconds()), roundCounter);
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
		sf::Packet packet;
		for (int i = 0; i < NUMBER_OF_RECEIVE_ATTEMPTS; ++i) {
			sf::Socket::Status status = socket.receive(packet);
			if (status == sf::Socket::Status::Done) {
				std::cout << "received packet" << std::endl;
				packetsReceived.push_back(packet);
			}
		}
	}

	void ClientApp::sendActionToServer(ActionPacket actionPacket) {
		sf::Packet packet;
		PacketType packetType = PacketType::ACTION_PACKET;
		packet << packetType;
		packet << actionPacket;
		std::cout << "action packet sent" << std::endl;
		std::cout << "action packet type: " << static_cast<int>(actionPacket.actionType) << std::endl;
		std::cout << "action packet source ID: " << actionPacket.sourceID << std::endl;
		std::cout << "action packet target ID: " << actionPacket.targetID << std::endl;
		packetsToSend.push_back(packet);
	}


	void ClientApp::sendPackets() {
		for (int i = 0; i < packetsToSend.size(); ++i)
			if (socket.send(packetsToSend[i]) == sf::Socket::Status::Done)
				packetsToSend.erase(packetsToSend.begin() + i--);
	}



} // namespace TheTraitor