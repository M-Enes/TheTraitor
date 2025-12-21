#include "GameHost.h"

#include <SFML/Network.hpp>

#include "GameManager.h"
#include "Country.h"

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
void TheTraitor::GameHost::update(){

}
void TheTraitor::GameHost::establishConnectionWithClients(){
    short connectedCount = 0;

    sf::TcpListener listener;
    if(listener.listen(53000) != sf::Socket::Status::Done){
        //error
    }

    while(connectedCount < 5){
        //accept a new connection
        sf::TcpSocket* client = new sf::TcpSocket();
        if(listener.accept(*client) != sf::Socket::Status::Done){
            //error
        } else {
            //add client to list
            Country* country = new Country(); // Randomly generate country stats here later
            Player player = Player("Player " + std::to_string(connectedCount + 1), country);
            client->setBlocking(false);
            player.setSocket(client);
            state.players.push_back(player);
            connectedCount++;
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

void TheTraitor::GameHost::run(){
    establishConnectionWithClients();
}

