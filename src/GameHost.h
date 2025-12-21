#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "GlobalGameState.h"
#include "GameState.h"
#include "GameManager.h"

namespace TheTraitor{
    class GameHost {
    private:
        // std::vector<> clientListeners
        // std::vector<> clientSockets
        int clientConnectionTimeout;
        bool isGameStarted;
        GlobalGameState state;
        GameManager gameManager;
        sf::IpAddress serverIp;
        unsigned short serverPort;

        //void receiveActionsFromClients(std::vector<> clientSockets);
        //void sendGameStateToClients(std::vector<> clientSockets);
        void kickDisconnectedClient();
        GameState* prepareGameStateForClient(int clientID);
        void updateGlobalGameState();
        
    public:
        GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/);
        void update();
        void establishConnectionWithClients();
        void receivePacket(sf::TcpSocket* socket);
        void sendPacket(sf::TcpSocket* socket, sf::Packet& packet);
        void run();
        void setIpAndPort(sf::IpAddress ip, unsigned short port){
            serverIp = ip;
            serverPort = port;
        }
    };
}