#pragma once

#include <vector>

#include "Player.h"
#include "GameState.h"
namespace TheTraitor {
        
    typedef struct GlobalGameState {
        // All public game information received from the server.
            GamePhase currentPhase;
            std::vector<TheTraitor::Player> players;
    } GlobalGameState;

} // namespace TheTraitor