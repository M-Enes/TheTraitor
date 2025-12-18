#include <iostream>
#include <string>

#include "Phase.h"

TheTraitor::Phase::Phase() {
    this->name = "Default Phase";
    this->durationTimeSeconds = 0;
}

TheTraitor::Phase::Phase(std::string name, int durationTimeSeconds) {
    this->name = name;
    this->durationTimeSeconds = durationTimeSeconds;
}

std::string TheTraitor::Phase::getName() {
    return this->name;
}

int TheTraitor::Phase::getDurationTimeSeconds() {
    return this->durationTimeSeconds;
}