#pragma once

#include <vector>
#include <ctime>

#include "Player.h"
#include "Phase.h"
#include "ActionPacket.h"

namespace TheTraitor{
    class GameManager {
        private:
            std::vector<Phase> phases;
            int currentPhaseIndex;
            std::clock_t currentPhaseTimer;
            void goToNextPhase();
            void resetCurrentPhaseTimer();
        public:
            GameManager();
            std::vector<Player> players;
            void update();
            void processAction(ActionPacket actionPacket);
            void addPlayer(const std::string& playerName);
            std::vector<std::string> getPlayers() const;
    };
}