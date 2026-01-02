#pragma once

#include <vector>
#include <ctime>
#include <SFML/Network.hpp>

#include "Common/ActionPacket.h"
#include "Common/GlobalGameState.h"

namespace TheTraitor{
    /**
	 * @brief Manages the main server loop and game logic.
	 */
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
            /**
             * @brief Constructor for GameManager.
             */
            GameManager();

            /**
             * @brief Updates the game state (timer, phases).
             */
            void update();

            /**
             * @brief Processes an incoming action packet.
             * @param actionPacket The packet containing the action.
             */
            void processAction(ActionPacket actionPacket);

            /**
             * @brief Runs the main server loop.
             */
            void run();
            
    };
}