#include <iostream>
#include <ctime>
#include <random>

#include "Player.h"

static int idBase = 0;


TheTraitor::Player::Player(std::string name, TheTraitor::Country* country) : country(country) {
    this->name = name;

    // Generating a random number
    if (idBase == 0) {
        std::srand(std::time(nullptr));
        idBase = std::rand() % 100000;
    }

    this->playerID = idBase++;
    
}

// Default Constructor
TheTraitor::Player::Player() {
    this->name = "Unnamed Player";
    this->country = new TheTraitor::Country();

    // Generating a random number
    if (idBase == 0) {
        std::srand(std::time(nullptr));
        idBase = std::rand() % 100000;
    }

    this->playerID = idBase++;
}

// Name
void TheTraitor::Player::setName(std::string name) {
    this->name = name;
}

std::string TheTraitor::Player::getName() const {
    return this->name;
}

// Country
void TheTraitor::Player::setCountry(Country* country) {
    this->country = country;
}

TheTraitor::Country* TheTraitor::Player::getCountry() const {
    return this->country;
}

// Role
void TheTraitor::Player::setRole(Role* role) {
    this->role = role;
}

TheTraitor::Role* TheTraitor::Player::getRole() const {
    return this->role;
}

void TheTraitor::Player::setSocket(sf::TcpSocket* socket) {
    this->socket = socket;
}

sf::TcpSocket* TheTraitor::Player::getSocket() const {
    return this->socket;
}