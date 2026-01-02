#pragma once

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "InputHandler.h"
#include "GameView.h"
#include "Common/PacketType.h"

#define NUMBER_OF_RECEIVE_ATTEMPTS 20

namespace TheTraitor {

	/**
	 * @brief The main application class for the Client.
	 * 
	 * Handles the game loop, network communication, input, and rendering.
	 */
	class ClientApp
	{
	public:
		/**
		 * @brief Constructor for ClientApp.
		 * @param executableFolderPath The path to the executable folder, used for loading assets.
		 */
		ClientApp(std::string executableFolderPath);

		ClientApp(const ClientApp&) = delete;
		ClientApp& operator=(const ClientApp&) = delete;

		/**
		 * @brief Runs the main application loop.
		 */
		void run();

		/**
		 * @brief Sends an action packet to the server.
		 * @param actionPacket The action packet to send.
		 */
		void sendActionToServer(ActionPacket actionPacket);
	private:
		sf::ContextSettings windowSettings;
		sf::RenderWindow window;
		InputHandler inputHandler;
		GameView gameView;
		unsigned short serverPort;
		sf::IpAddress serverIp;
		GameState gameState;
		sf::Music menuMusic;
		sf::Music actionPhaseMusic;
		sf::Music winMusic;
		sf::Music gameoverMusic;
		sf::TcpSocket socket;
		std::vector<sf::Packet> packetsToSend;
		std::vector<sf::Packet> packetsReceived;

		int playerID;

		// Flags
		bool isIDReceived = false;
		bool isNameAndAvatarSent = false;
		bool isConnected;

		sf::Clock totalTimer;
		sf::Clock phaseTimer;
		int roundCounter = 1;
	private:
		/**
		 * @brief Updates the application state.
		 * @param deltaTime Time elapsed since the last frame.
		 */
		void update(sf::Time deltaTime);
		void updateMenu();
		void updateLobby();
		void updateDiscussionPhase();
		void updateActionPhase();
		void updateResolutionPhase();
		void updateGameover();
		void updateWin();
		void render();
		void openTCPSocket(sf::IpAddress ip, unsigned short port);
		void receivePackets();
		void sendPackets();

		// Resolution Phase State
		int expectedResolutionActionCount = -1;
		std::vector<ActionPacket> resolutionActions;
		bool resolutionActionsReceived = false;
		GameState pendingGameState;
		bool hasPendingGameState = false;
		bool resolutionTimerStarted = false;
	};
}
