#include <iostream>
#include <string>

#include "SecretAction.h"

namespace TheTraitor {
    SecretAction::SecretAction() : Action() {}

    void SecretAction::execute(const Player& player1, const Player& player2) {
        std::cout << player1.getName() << " has performed a secret action involving " << player2.getName() << "." << std::endl;
        // Additional logic for the secret action can be added here
    }

    std::string SecretAction::getLogMessage(const Player& player1, const Player& player2) {
        return player1.getName() + " performed a secret action involving " + player2.getName() + ".";
    }
}