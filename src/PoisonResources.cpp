#include <iostream>
#include <string>

#include "PoisonResources.h"

namespace TheTraitor {
    PoisonResources::PoisonResources() : Action() {}

    void PoisonResources::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        player1.getCountry().getHealth() -= 10;
        player2.getCountry().getEconomy() -= 10;
        if (player2.getCountry().getEconomy() < 0) {
            player2.getCountry().setDestroyed();
        }
        if (player1.getCountry().getHealth() < 10) {
            player1.getCountry().getEconomy() -= 5;
        }
    }

    std::string PoisonResources::getLogMessage(const Player& player1, const Player& player2) {
        return player2.getName() + " poisoned the resources of " + player1.getName() + ".";
    }
}