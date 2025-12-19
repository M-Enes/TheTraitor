#include <iostream>
#include <string>

#include "SabotageFactory.h"

namespace TheTraitor {
    SabotageFactory::SabotageFactory() : Action() {}

    void SabotageFactory::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        player2.getCountry().getEconomy() -= 10;
        
        if (player2.getCountry().getEconomy() < 0) {
            player2.getCountry().setDestroyed();
        }
    }
        
    std::string SabotageFactory::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " sabotaged the factory of " + player2.getName() + ".";
    }
}