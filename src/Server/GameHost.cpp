#include "GameHost.h"

#include <SFML/Network.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>

#include "Common/Country.h"
#include "Common/PacketType.h"
#include "Common/Role.h"

namespace TheTraitor {

	GameHost::GameHost() : serverIp(sf::IpAddress::LocalHost), serverPort(53000) {
		clientConnectionTimeout = 30; //seconds
		isGameStarted = false;

		std::cout << "Game Host created at " << serverIp.toString() << ":" << serverPort << std::endl;

	}

	void GameHost::establishConnectionWithClients(GlobalGameState& state) {
		state.currentPhase = LOBBY;
		short connectedCount = 0;

		std::vector<Country::CountryType> availableTypes = {
			Country::CountryType::AMERICA,
			Country::CountryType::AFRICA,
			Country::CountryType::EUROPE,
			Country::CountryType::ASIA,
			Country::CountryType::AUSTRALIA
		};
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(availableTypes.begin(), availableTypes.end(), g);

		sf::TcpListener listener;
		if (listener.listen(serverPort) != sf::Socket::Status::Done) {
			//error
			std::cout << "Error: Could not start listening on port " << serverPort << std::endl;
		}

		while (connectedCount < 5) {
			//accept a new connection
			sf::TcpSocket* client = new sf::TcpSocket();
			std::string playerName;
			int avatarID;
			if (listener.accept(*client) != sf::Socket::Status::Done) {
				//error
			}
			else {
				std::cout << "New client connected: " << std::endl;

				Country* country = new Country(); // TODO: Randomly generate country stats here later
				if (!availableTypes.empty()) {
					country->setType(availableTypes.back());
					availableTypes.pop_back();
				}

				// Receive player name and avatarID
				bool isNameReceived = false;
				bool isAvatarReceived = false;
				while ( !isNameReceived || !isAvatarReceived ) {
					// Wait until both name and avatarID are received
					// Get name from client
					sf::Packet namePacket;
					if (client->receive(namePacket) == sf::Socket::Status::Done && !isNameReceived) {
						PacketType packetType;
						namePacket >> packetType;
						if (packetType == PacketType::STRING) {
							// Get the name of the player
							namePacket >> playerName;
							isNameReceived = true;
							std::cout << "Player name received: " << playerName << std::endl;
						}
					}

					// Get avatarID from client
					sf::Packet avatarPacket;
					if (client->receive(avatarPacket) == sf::Socket::Status::Done && !isAvatarReceived) {
						PacketType packetType;
						avatarPacket >> packetType;
						if (packetType == PacketType::INT) {
							// Get the avatarID of the player
							avatarPacket >> avatarID;
							isAvatarReceived = true;
							std::cout << "Avatar ID received: " << avatarID << std::endl;
						}
					}
				}

				// Create player and add to global game state
				Player player = Player(playerName, country, avatarID);
				player.setSocket(client);
				player.setRole(new Innocent());
				state.players.push_back(player);

				std::cout << "Player " << playerName << " joined the game with ID " << player.getPlayerID() << std::endl;

				// Send playerID to client
				sf::Packet playerIDPacket;
				PacketType playerIDPacketType = PacketType::INT;
				playerIDPacket << playerIDPacketType;
				playerIDPacket << player.getPlayerID();
				if (client->send(playerIDPacket) != sf::Socket::Status::Done){
					//error
					std::cout << "Error: Could not send player ID to client." << std::endl;
				}

				connectedCount++;
				
				// Send updated game state to all players
				for (auto& player : state.players) {
					sf::TcpSocket* socket = player.getSocket();
					GameState gameState;
					PacketType gameStatePacketType = PacketType::GAMESTATE;
					sf::Packet gameStatePacket;
					gameStatePacket << gameStatePacketType;
					gameState.currentPhase = state.currentPhase;
					gameState.players = state.players;
					gameStatePacket << gameState;
					if (socket->send(gameStatePacket) != sf::Socket::Status::Done)
					{
						//error
					}
				}
			}
		}
	}

	void GameHost::receivePacket(sf::TcpSocket* socket) {
		sf::Packet packet;
		if (socket->receive(packet) != sf::Socket::Status::Done) {
			//error
			return;
		} else {
			// Process packet
			std::cout << "Packet received from client: " << std::endl;
		}
		
	}

	void GameHost::sendPacket(sf::TcpSocket* socket, sf::Packet& packet) {
		if (socket->send(packet) != sf::Socket::Status::Done) {
			//error
		} else {
			std::cout << "Packet sent to client: " << std::endl;
		}
	}

	void GameHost::setIpAndPort(sf::IpAddress ip, unsigned short port){
            serverIp = ip;
            serverPort = port;
    }
}