#include <iostream>
#include "Country.h"

TheTraitor::Country::Country(int economy, int health, int education, CountryType type) {
    this->economy = economy;
    this->health = health;
    this->education = education;
    this->destroyed = false;
    this->type = type;
}


TheTraitor::Country::Country() {
    this->economy = 0;
    this->health = 0;
    this->education = 0;
    this->destroyed = false;
    this->type = CountryType::NONE;
}

TheTraitor::Country::CountryType TheTraitor::Country::getType() const {
    return this->type;
}

void TheTraitor::Country::setType(CountryType type) {
    this->type = type;
}

int TheTraitor::Country::getEconomy() const {
    return this->economy;
}

int TheTraitor::Country::getHealth() const {
    return this->health;
}

int TheTraitor::Country::getEducation() const {
    return this->education;
}

bool TheTraitor::Country::isDestroyed() const {
    return this->destroyed;
}

void TheTraitor::Country::setEconomy(int economy) {
    if (economy < 0) {
        economy = 0;
    }
    else if (economy > 100) {
        economy = 100;
    }
    this->economy = economy;
}

void TheTraitor::Country::setHealth(int health) {
    if (health < 0) {
        health = 0;
    }
    else if (health > 100) {
        health = 100;
    }
    this->health = health;
}

void TheTraitor::Country::setEducation(int education) {
    if (education < 0) {
        education = 0;
    }
    else if (education > 100) {
        education = 100;
    }
    this->education = education;
}


void TheTraitor::Country::checkDestroyed() {
    // Destroyed if any stat reaches 0
    // Maybe change this condition later
    if (economy == 0 || health == 0 || education == 0) {
        destroyed = true;
    } else {
        destroyed = false;
    }
}

void TheTraitor::Country::setDestroyed(bool destroyed) {
    this->destroyed = destroyed;
}