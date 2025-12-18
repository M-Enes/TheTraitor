#include <iostream>
#include <string>

#include "DestroySchool.h"

namespace TheTraitor {
    DestroySchool::DestroySchool() : Action() {}

    void DestroySchool::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has destroyed the school of " << player2.getName() << "." << std::endl;
        // Additional logic for destroying the school can be added here
    }

    std::string DestroySchool::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " destroyed the school of " + player2.getName() + ".";
    }
}