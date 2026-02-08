#include "GameHost.h"
#include <iostream>

int main(int argc, char* argv[]) {
    unsigned short serverPort = 53000;
    if (argc == 2) {
        serverPort = std::stoi(argv[1]);
    }

    TheTraitor::GameManager gameManager(serverPort);
    gameManager.run();
    return 0;
}