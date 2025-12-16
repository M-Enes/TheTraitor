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