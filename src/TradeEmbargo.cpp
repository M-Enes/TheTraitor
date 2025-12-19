#include <iostream>
#include <string>

#include "TradePact.h"

namespace TheTraitor {
    TradeEmbargo::TradeEmbargo() : Action() {}

    void TradeEmbargo::execute(const Player& player1, const Player& player2) {
        std::cout << getLogMessage(player1, player2) << std::endl;
        // Implementation of the trade embargo effect would go here
    }

    std::string TradeEmbargo::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " formed a trade embargo with " + player2.getName() + ".";
    }
}