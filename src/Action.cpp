#include <iostream>

#include "Action.h"

namespace TheTraitor {

    std::string Action::getLogMessage() {
        return "Action executed.";
    }

    void Action::execute(Player* player1, Player* player2) {
        std::cout << "Executing base Action between " 
                  << player1->getName() << " and " 
                  << player2->getName() << std::endl;
    }
    
} 