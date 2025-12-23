#pragma once

#include <vector>
#include <ctime>

#include "Common/Player.h"
#include "Common/Phase.h"
#include "Common/ActionPacket.h"
#include "Common/GlobalGameState.h"

namespace TheTraitor{
    class GameManager {
        private:
            int traitorIndex;
            int currentPhaseIndex;
            std::clock_t currentPhaseTimer;
            void goToNextPhase();
            void resetCurrentPhaseTimer();
            void sendGameStateToAllPlayers();
        public:
            GlobalGameState state;
            GameManager();
            int clientConnectionTimeout;
            bool isGameStarted;
            void update();
            void processAction(ActionPacket actionPacket);
            void addPlayer(const std::string& playerName);
            std::vector<std::string> getPlayers() const;
            void run();
            
    };
}