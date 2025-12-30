#pragma once

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "InputHandler.h"
#include "GameView.h"
#include "Common/PacketType.h"

#define NUMBER_OF_RECEIVE_ATTEMPTS 20

namespace TheTraitor {

	class ClientApp
	{
	public:
		ClientApp(std::string executableFolderPath);
		ClientApp(const ClientApp&) = delete;
		ClientApp& operator=(const ClientApp&) = delete;
		void run();
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
	};
}
