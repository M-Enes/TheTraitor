#include <iostream>
#include <string>

#include "Role.h"

namespace TheTraitor {
    Role::Role(std::string name) : name(name) {

    }

    std::string Role::getName() {
        return name;
    }

    std::vector<Action*> Role::getPublicActions() {
        return std::vector<Action*>();
    }

    std::vector<SecretAction*> Role::getSecretActions() {
        return std::vector<SecretAction*>();
    }

}