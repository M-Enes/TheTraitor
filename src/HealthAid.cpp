#include <iostream>
#include <string>

#include "HealthAid.h"

namespace TheTraitor {
    HealthAid::HealthAid() : Action() {}

    void HealthAid::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " is providing health aid to " << player2.getName() << "." << std::endl;
        // Additional logic for providing health aid can be added here
    }

    std::string HealthAid::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " provided health aid to " + player2.getName() + ".";
    }
}