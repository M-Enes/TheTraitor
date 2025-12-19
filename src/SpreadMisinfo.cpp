#include <iostream>
#include <string>

#include "SpreadMisinfo.h"

namespace TheTraitor {
    SpreadMisinfo::SpreadMisinfo() : Action() {}

    void SpreadMisinfo::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        // Implementation of the misinformation effect would go here
    }

    std::string SpreadMisinfo::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " spread misinformation about " + player2.getName() + ".";
    }
}