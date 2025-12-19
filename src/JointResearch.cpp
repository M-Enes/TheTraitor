#include <iostream>
#include <string>

#include "JointResearch.h"

namespace TheTraitor {
    JointResearch::JointResearch() : Action() {}

    void JointResearch::execute(const Player& player1, const Player& player2) {
        if (player1.getCountry().getEconomy() < 5 || player2.getCountry().getEconomy() < 5) {
            std::cout << "Joint research failed due to insufficient economy." << std::endl;
            return;
        }
        std::cout << getLogMessage(player1, player2) << std::endl;
        player1.getCountry().getEconomy() -= 5;
        player1.getCountry().getEducation() += 10;
        player2.getCountry().getEconomy() -= 5;
        player2.getCountry().getEducation() += 10;
    }

    std::string JointResearch::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " conducted joint research with " + player2.getName() + ".";
    }
}