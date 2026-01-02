#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "Common/GlobalGameState.h"
#include "Common/GameState.h"
#include "GameManager.h"

namespace TheTraitor{
    	/**
	 * @brief Handles low-level network communication for the server.
	 */
	class GameHost {
	private:
		int clientConnectionTimeout;
		bool isGameStarted;
		sf::IpAddress serverIp;
		unsigned short serverPort;

	private:
		void kickDisconnectedClient();
		GameState* prepareGameStateForClient(int clientID);
		void updateGlobalGameState();
		
	public:
		/**
		 * @brief Constructor for GameHost.
		 */
		GameHost();

		/**
		 * @brief Establishes connections with waiting clients.
		 * @param state The global game state to populate with connected players.
		 */
		void establishConnectionWithClients(GlobalGameState& state);

		/**
		 * @brief Receives a packet from a client.
		 * @param socket The socket to receive from.
		 */
		void receivePacket(sf::TcpSocket* socket);

		/**
		 * @brief Sends a packet to a client.
		 * @param socket The socket to send to.
		 * @param packet The packet to send.
		 */
		void sendPacket(sf::TcpSocket* socket, sf::Packet& packet);

		/**
		 * @brief Sets the server's IP and port.
		 * @param ip The IP address.
		 * @param port The port number.
		 */
		void setIpAndPort(sf::IpAddress ip, unsigned short port);
	};
}