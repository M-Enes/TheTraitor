#pragma once

#include <string>

namespace TheTraitor {
    class Player;

    class Action {
    public:
        virtual void execute(Player* player1, Player* player2) = 0;
        virtual std::string getLogMessage(Player* player1, Player* player2) = 0;
    protected:
        Action() = default; // allow derived classes to construct
    };
}