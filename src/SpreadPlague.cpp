#include <iostream>
#include <string>

#include "SpreadPlague.h"

namespace TheTraitor {
    SpreadPlague::SpreadPlague() : Action() {}

    void SpreadPlague::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        player2.getCountry().getHealth() -= 10;
        if (player2.getCountry().getHealth() < 10) {
            player2.getCountry().getEconomy() -= 5;
        }
    }

    std::string SpreadPlague::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " spread a plague to " + player2.getName() + ".";
    }
}