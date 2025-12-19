#include "GameHost.h"

#include <SFML/Network.hpp>
#include <iostream>

#include "GameManager.h"
#include "Country.h"
#include "PacketType.h"

TheTraitor::GameHost::GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/){

}

/*void receiveActionsFromClients(std::vector<> clientSockets){

}*/

/*void sendGameStateToClients(std::vector<> clientSockets){

}*/

void TheTraitor::GameHost::kickDisconnectedClient(){

}
TheTraitor::GameState* TheTraitor::GameHost::prepareGameStateForClient(int clientID){
    return nullptr;
}
void TheTraitor::GameHost::updateGlobalGameState(){

}
void TheTraitor::GameHost::update(){

}
void TheTraitor::GameHost::establishConnectionWithClients(GameManager* gameManager){
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
            // #########################################################################################
            // Testing receiving initial packet from client
           // TheTraitor::Packet* initialPacket = receivePacket(client); 
            sf::Packet packet;
            PacketType packetType;
            if (client->receive(packet) != sf::Socket::Status::Done) {
                packetType = PacketType::UNKNOWN;
                //error
            }
            else {
                packet >> packetType;
            }
            std::string receivedStr;
            packet >> receivedStr;
            std::cout << "Packet type: " << static_cast<int>(packetType) << std::endl;
            std::cout << "Received string: " << receivedStr << std::endl;
            //if (initialPacket == nullptr) {
            //    std::cout << "Error receiving initial packet from client." << std::endl;
            //} else if (initialPacket->string) {
            //    std::cout << "Client connected with name: " << initialPacket->data.string << std::endl;
            //}
            //// #########################################################################################
            //Player* player = new Player("Player", country);
            //client->setBlocking(false);
            //player->setSocket(client);
            //gameManager->players.push_back(player);
            //connectedCount++;
        }
    }
}

void TheTraitor::GameHost::run(){
    GameManager* gameManager = new GameManager();
    establishConnectionWithClients(gameManager);
}