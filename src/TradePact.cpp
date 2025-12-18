#include <iostream>
#include <string>

#include "TradePact.h"

namespace TheTraitor {
    TradePact::TradePact() : Action() {}

    void TradePact::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has formed a trade pact with " << player2.getName() << "." << std::endl;
        // Additional logic for forming a trade pact can be added here
    }

    std::string TradePact::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " formed a trade pact with " + player2.getName() + ".";
    }
}