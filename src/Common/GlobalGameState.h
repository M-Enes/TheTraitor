#pragma once

#include <vector>

#include "Player.h"
#include "GameState.h"
namespace TheTraitor {
        
    /**
     * @brief Struct representing the global game state maintained by the server.
     */
    typedef struct GlobalGameState {
        // All public game information received from the server.
            GamePhase currentPhase; ///< The current game phase.
            std::vector<TheTraitor::Player> players; ///< The list of all players in the game.
    } GlobalGameState;

} // namespace TheTraitor