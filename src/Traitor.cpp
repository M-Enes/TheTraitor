#include <iostream>

#include "Traitor.h"

class Traitor;

TheTraitor::Traitor::Traitor() : Role("Traitor") { //Çok object oriented oldu bu yaa :)

}

std::vector<TheTraitor::SecretAction> TheTraitor::Traitor::getSecretActions() {
    return std::vector<SecretAction>{};
}