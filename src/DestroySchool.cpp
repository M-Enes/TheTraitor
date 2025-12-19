#include <iostream>
#include <string>

#include "DestroySchool.h"

namespace TheTraitor {
    DestroySchool::DestroySchool() : Action() {}

    void DestroySchool::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        player2.getCountry().getEducation() -= 10;
        if (player2.getCountry().getEducation() < 0) {
            player2.getCountry().getEducation() = 0;
        }
    }

    std::string DestroySchool::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " destroyed the school of " + player2.getName() + ".";
    }
}