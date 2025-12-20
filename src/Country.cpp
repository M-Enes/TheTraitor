#include <iostream>
#include "Country.h"

TheTraitor::Country::Country(int economy, int health, int education) {
    this->economy = economy;
    this->health = health;
    this->education = education;
    this->destroyed = false;
}


TheTraitor::Country::Country() {
    this->economy = 0;
    this->health = 0;
    this->education = 0;
    this->destroyed = false;
}

int TheTraitor::Country::getEconomy() {
    return this->economy;
}

int TheTraitor::Country::getHealth() {
    return this->health;
}

int TheTraitor::Country::getEducation() {
    return this->education;
}

bool TheTraitor::Country::isDestroyed() {
    return this->destroyed;
}

void TheTraitor::Country::setDestroyed() {
    this->destroyed = true;
}

void TheTraitor::Country::setEconomy(int economy) {
    this->economy = economy;
}

void TheTraitor::Country::setHealth(int health) {
    this->health = health;
}

void TheTraitor::Country::setEducation(int education) {
    this->education = education;
}

void TheTraitor::Country::setDestroyed(bool destroyed) {
    this->destroyed = destroyed;
}