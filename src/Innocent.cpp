#include <iostream>

#include "Innocent.h"

class Innocent;

TheTraitor::Innocent::Innocent() : Role("Innocent") {

}

std::vector<TheTraitor::SecretAction> TheTraitor::Innocent::getSecretActions() {
    return std::vector<SecretAction>{};
}