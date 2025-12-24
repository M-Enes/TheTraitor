#pragma once

#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "InputHandler.h"
#include "GameView.h"
#include "Common/PacketType.h"

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
		sf::TcpSocket socket;
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
	};
}
