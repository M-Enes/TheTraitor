#pragma once

#include <string>
#include <vector>

#include "Player.h"
namespace TheTraitor {
    enum GamePhase {
            MENU,
            LOBBY,
            DISCUSSION_PHASE,
            ACTION_PHASE,
            RESOLUTION_PHASE,
            GAMEOVER,
            WIN
        };

    typedef struct GameStateData {
        // All public game information received from the server.
        GamePhase currentPhase;
        std::vector<TheTraitor::Player> players;

    } GameStateData;
} // namespace TheTraitor