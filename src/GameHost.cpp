#include "GameHost.h"

#include <SFML/Network.hpp>

#include "GameManager.h"
#include "Country.h"

TheTraitor::GameHost::GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/){

}

/*void receiveActionsFromClients(std::vector<> clientSockets){

}*/

/*void sendGameStateToClients(std::vector<> clientSockets){

}*/

void TheTraitor::GameHost::kickDisconnectedClient(){

}
GameState* TheTraitor::GameHost::prepareGameStateForClient(int clientID){
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
            Player* player = new Player("Player", country);
            client->setBlocking(false);
            player->setSocket(client);
            gameManager->players.push_back(player);
            connectedCount++;
        }
    }
}

void TheTraitor::GameHost::run(){
    GameManager* gameManager = new GameManager();
    establishConnectionWithClients(gameManager);
}