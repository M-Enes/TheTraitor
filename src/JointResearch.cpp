#include <iostream>
#include <string>

#include "JointResearch.h"

namespace TheTraitor {
    JointResearch::JointResearch() : Action() {}

    void JointResearch::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " is conducting joint research with " << player2.getName() << "." << std::endl;
        // Additional logic for joint research can be added here
    }

    std::string JointResearch::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " conducted joint research with " + player2.getName() + ".";
    }
}