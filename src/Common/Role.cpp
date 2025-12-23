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


    Traitor::Traitor() : Role("Traitor") {

    }

    std::vector<SecretAction*> Traitor::getSecretActions() {
        return std::vector<SecretAction*>{};
    }

    Innocent::Innocent() : Role("Innocent") {

    }

    std::vector<SecretAction*> TheTraitor::Innocent::getSecretActions() {
        return std::vector<SecretAction*>{};
    }

}