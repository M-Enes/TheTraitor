#pragma once

#include <string>
#include <vector>

#include "Player.h"

namespace TheTraitor {
	/**
	 * @brief Enumeration of the different game phases.
	 */
    enum GamePhase {
        MENU,             ///< Main menu phase.
        LOBBY,            ///< Lobby where players wait for the game to start.
        DISCUSSION_PHASE, ///< Phase for players to discuss strategies.
        ACTION_PHASE,     ///< Phase where players select actions.
        RESOLUTION_PHASE, ///< Phase where actions are resolved and results shown.
        GAMEOVER,         ///< Game over screen (loss).
        WIN,              ///< Win screen (victory).
        NONE              ///< No specific phase or invalid.
    };

    /**
     * @brief Struct representing the state of the game sent to clients.
     */
    typedef struct GameState {
        // All public game information received from the server.
        GamePhase currentPhase; ///< The current phase of the game.
        std::vector<TheTraitor::Player> players; ///< List of players in the game.

    } GameState;
} // namespace TheTraitor