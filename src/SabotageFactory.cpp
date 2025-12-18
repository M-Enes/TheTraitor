#include <iostream>
#include <string>

#include "SabotageFactory.h"

namespace TheTraitor {
    SabotageFactory::SabotageFactory() : Action() {}

    void SabotageFactory::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has sabotaged the factory of " << player2.getName() << "." << std::endl;
        // Additional logic for sabotaging the factory can be added here
    }

    std::string SabotageFactory::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " sabotaged the factory of " + player2.getName() + ".";
    }
}