#include <iostream>
#include <string>

#include "SpreadMisinfo.h"

namespace TheTraitor {
    SpreadMisinfo::SpreadMisinfo() : Action() {}

    void SpreadMisinfo::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " is spreading misinformation about " << player2.getName() << "." << std::endl;
        // Additional logic for spreading misinformation can be added here
    }

    std::string SpreadMisinfo::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " spread misinformation about " + player2.getName() + ".";
    }
}