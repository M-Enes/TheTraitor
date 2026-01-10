#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>

#include "Common/GlobalGameState.h"
#include "Common/GameState.h"
#include "GameManager.h"

namespace TheTraitor{
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
        GameHost();
        void establishConnectionWithClients(GlobalGameState& state);
        void receivePacket(sf::TcpSocket* socket);
        void sendPacket(sf::TcpSocket* socket, sf::Packet& packet);
        void setIpAndPort(sf::IpAddress ip, unsigned short port);
    };
}