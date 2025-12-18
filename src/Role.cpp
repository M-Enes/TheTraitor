#include <iostream>
#include <string>

#include "Role.h"

namespace TheTraitor {
    Role::Role(std::string name) : name(name) {

    }

    std::string Role::getName() {
        return name;
    }

    std::vector<TheTraitor::Action> Role::getPublicActions() {
        return std::vector<TheTraitor::Action>();
    }

    std::vector<TheTraitor::SecretAction> Role::getSecretActions() {
        return std::vector<TheTraitor::SecretAction>();
    }

}