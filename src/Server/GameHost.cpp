#include "GameHost.h"
#include <SFML/Network.hpp>
#include <vector>
#include <algorithm>
#include "Common/Country.h"
#include "Common/PacketType.h"

TheTraitor::GameHost::GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/) : serverIp(sf::IpAddress::LocalHost), serverPort(53000){
    clientConnectionTimeout = 30; //seconds
    isGameStarted = false;

}

void TheTraitor::GameHost::kickDisconnectedClient(){

}
TheTraitor::GameState* TheTraitor::GameHost::prepareGameStateForClient(int clientID){
    return nullptr;
}
void TheTraitor::GameHost::updateGlobalGameState(){
    

}


void TheTraitor::GameHost::establishConnectionWithClients(GlobalGameState& state) {
    state.currentPhase = LOBBY;
    short connectedCount = 0;

    sf::TcpListener listener;
    if(listener.listen(serverPort) != sf::Socket::Status::Done) {
        //error
    }
    while(connectedCount < 5) {
        //accept a new connection
        sf::TcpSocket* client = new sf::TcpSocket();
        if(listener.accept(*client) != sf::Socket::Status::Done){
            //error
        } else {
            //add client to list
            Country* country = new Country(); // TODO: Randomly generate country stats here later
            
            // Get name from client
            sf::Packet namePacket;
            if (client->receive(namePacket) != sf::Socket::Status::Done) {
                //error
            } else {
                std::string playerName;
                PacketType packetType;
                namePacket >> packetType;
                if (packetType != PacketType::STRING) {
                    //error
                } else {
                    // Get the name of the player
                    namePacket >> playerName;
                    Player player = Player(playerName, country);
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
    }
}

void receivePacket(sf::TcpSocket* socket) {
    sf::Packet packet;
    if (socket->receive(packet) != sf::Socket::Status::Done) {
        //error
        return;
    }

    // Process packet as needed
}

void sendPacket(sf::TcpSocket* socket, sf::Packet& packet) {
    if (socket->send(packet) != sf::Socket::Status::Done) {
        //error
    }
}

