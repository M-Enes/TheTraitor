#include <iostream>
#include <string>

#include "HealthAid.h"

namespace TheTraitor {
    HealthAid::HealthAid() : Action() {}

    void HealthAid::execute(const Player& player1, const Player& player2) {
        if (player1.getCountry().getEconomy() < 10) {
            std::cout << "Health aid failed due to insufficient economy." << std::endl;
            return;
        }
        std::cout << getLogMessage(player1, player2) << std::endl;
        player1.getCountry().getEconomy() -= 10;
        player2.getCountry().getHealth() += 15;
    }

    std::string HealthAid::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " provided health aid to " + player2.getName() + ".";
    }
}