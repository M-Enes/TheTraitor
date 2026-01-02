#pragma once

#include <vector>
#include <ctime>
#include <SFML/Network.hpp>

#include "Common/ActionPacket.h"
#include "Common/GlobalGameState.h"

namespace TheTraitor{
    class GameManager {
        private:
            int traitorIndex;
            int currentPhaseIndex;
            sf::Clock currentPhaseTimer;
            GlobalGameState state;
            sf::SocketSelector selector;
            std::vector<ActionPacket> actionPackets;

        private:
            void goToNextPhase();
            void resetCurrentPhaseTimer();
            void sendGameStateToAllPlayers();
            void sendActionPacketToAllPlayers(std::vector<ActionPacket> actionPackets);

        public:
            GameManager();
            void update();
            void processAction(ActionPacket actionPacket);
            void run();
            
    };
}