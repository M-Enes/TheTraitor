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

        //void receiveActionsFromClients(std::vector<> clientSockets);
        //void sendGameStateToClients(std::vector<> clientSockets);
        void kickDisconnectedClient();
        GameState* prepareGameStateForClient(int clientID);
        void updateGlobalGameState();
        
    public:
        GameHost(/*clientListeners, clientSockets, clientConnectionTimeout*/);
        void update();
        void establishConnectionWithClients(GameManager* gameManager);
        void run();
    };
}