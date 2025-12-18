#pragma once

#include <string>

#include "Player.h"

namespace TheTraitor {

    class Action {
    public:
        virtual void execute(Player* player1, Player* player2) = 0;
        virtual std::string getLogMessage(Player* player1, Player* player2) = 0;
    protected:
        Action() = default; // allow derived classes to construct
    };
}