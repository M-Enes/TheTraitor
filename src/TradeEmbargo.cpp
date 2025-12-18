#include <iostream>
#include <string>

#include "TradePact.h"

namespace TheTraitor {
    TradeEmbargo::TradeEmbargo() : Action() {}

    void TradeEmbargo::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has formed a trade embargo with " << player2.getName() << "." << std::endl;
        // Additional logic for forming a trade embargo can be added here
    }

    std::string TradeEmbargo::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " formed a trade embargo with " + player2.getName() + ".";
    }
}