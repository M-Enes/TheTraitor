#pragma once

#include <SFML/Network.hpp>
#include <string>

#include "InputHandler.h"
#include "GameView.h"
#include "Packet.h"
#include "PacketType.h"

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
		sf::RenderWindow window;
		InputHandler inputHandler;
		GameView gameView;
		unsigned short serverPort;
		sf::IpAddress serverIp;
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
		GameState gameState;
		sf::TcpSocket* openTCPSocket(sf::IpAddress ip, unsigned short port);
		void receivePackets(sf::TcpSocket& socket);
		void sendPacket(sf::TcpSocket* socket, Packet& packet);
	};
}
