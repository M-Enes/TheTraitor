#include <iostream>
#include <string>

#include "PoisonResources.h"

namespace TheTraitor {
    PoisonResources::PoisonResources() : Action() {}

    void PoisonResources::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " is poisoning the resources of " << player2.getName() << "." << std::endl;
        // Additional logic for poisoning resources can be added here
    }

    std::string PoisonResources::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " poisoned the resources of " + player2.getName() + ".";
    }
}