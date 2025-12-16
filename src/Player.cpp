#include <iostream>
#include <random>

#include "Player.h"

static int idBase = 0;


TheTraitor::Player::Player(std::string name, Country country) {
    this->name = name;
    this->country = country;

    // Generating a random number
    if (idBase == 0) {
        std::srand(std::time(nullptr));
        idBase = std::rand() % 100000;
    }

    this->playerID = idBase++;
    
}

// Name
void setName(std::string name) {
    this->name = name;
}

std::string TheTraitor::Player::getName() const {
    return this->name;
}

// Country
void TheTraitor::Player::setCountry(Country country) {
    this->country = country;
}

TheTraitor::Country TheTraitor::Player::getCountry() const {
    return this->country;
}

// Role
void TheTraitor::Player::setRole(Role role) {
    this->role = role;
}

TheTraitor::Role TheTraitor::Player::getRole() const {
    return this->role;
}

