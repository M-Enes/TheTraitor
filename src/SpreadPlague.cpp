#include <iostream>
#include <string>

#include "SpreadPlague.h"

namespace TheTraitor {
    SpreadPlague::SpreadPlague() : Action() {}

    void SpreadPlague::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has spread a plague to " << player2.getName() << "." << std::endl;
        // Additional logic for spreading the plague can be added here
    }

    std::string SpreadPlague::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " spread a plague to " + player2.getName() + ".";
    }
}