#include "Role.h"

namespace TheTraitor {
    Role::Role(std::string name) : name(name) {

    }

    std::string Role::getName() const {
        return name;
    }

    std::vector<Action*> Role::getPublicActions() const {
        return std::vector<Action*>();
    }

    std::vector<SecretAction*> Role::getSecretActions() const {
        return std::vector<SecretAction*>();
    }


    Traitor::Traitor() : Role("Traitor") {

    }

    std::vector<SecretAction*> Traitor::getSecretActions() const {
        return std::vector<SecretAction*>{};
    }

    Innocent::Innocent() : Role("Innocent") {

    }

    std::vector<SecretAction*> TheTraitor::Innocent::getSecretActions() const {
        return std::vector<SecretAction*>{};
    }

}