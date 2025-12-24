#include "GameHost.h"
#include <SFML/Network.hpp>
#include <vector>
#include <algorithm>
#include "Common/Country.h"
#include "Common/PacketType.h"

namespace TheTraitor {

	GameHost::GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/) : serverIp(sf::IpAddress::LocalHost), serverPort(53000) {
		clientConnectionTimeout = 30; //seconds
		isGameStarted = false;

	}

	void GameHost::kickDisconnectedClient() {

	}
	GameState* GameHost::prepareGameStateForClient(int clientID) {
		return nullptr;
	}
	void GameHost::updateGlobalGameState() {


	}


	void GameHost::establishConnectionWithClients(GlobalGameState& state) {
		state.currentPhase = LOBBY;
		short connectedCount = 0;

		sf::TcpListener listener;
		if (listener.listen(serverPort) != sf::Socket::Status::Done) {
			//error
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
				//add client to list
				Country* country = new Country(); // TODO: Randomly generate country stats here later
				bool isNameReceived = false;
				bool isAvatarReceived = false;

				while ( !isNameReceived || !isAvatarReceived ) {
					// Wait until both name and avatarID are received
					// Get name from client
					sf::Packet namePacket;
					if (client->receive(namePacket) == sf::Socket::Status::Done) {
						PacketType packetType;
						namePacket >> packetType;
						if (packetType == PacketType::STRING) {
							// Get the name of the player
							namePacket >> playerName;
							isNameReceived = true;
						}
					}

					// Get avatarID from client
					sf::Packet avatarPacket;
					if (client->receive(avatarPacket) == sf::Socket::Status::Done) {
						PacketType packetType;
						avatarPacket >> packetType;
						if (packetType == PacketType::INT) {
							// Get the avatarID of the player
							avatarPacket >> avatarID;
							isAvatarReceived = true;
						}
					}
				}

				// Create player and add to global game state
				Player player = Player(playerName, country, avatarID);
				player.setSocket(client);
				state.players.push_back(player);
				client->setBlocking(false);

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
		}

		// Process packet as needed
	}

	void GameHost::sendPacket(sf::TcpSocket* socket, sf::Packet& packet) {
		if (socket->send(packet) != sf::Socket::Status::Done) {
			//error
		}
	}

}