#include <iostream>
#include <string>

#include "TradePact.h"

namespace TheTraitor {
    TradePact::TradePact() : Action() {}

    void TradePact::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        player1.getCountry().getEconomy() += 5;
        player2.getCountry().getEconomy() += 5;
        if (player1.getCountry().getEconomy() > 100) { 
            player1.getCountry().getEconomy() = 100;
        }
        if (player2.getCountry().getEconomy() > 100) {
            player2.getCountry().getEconomy() = 100;
        }
    }

    std::string TradePact::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " formed a trade pact with " + player2.getName() + ".";
    }
}