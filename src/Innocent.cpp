#include <iostream>

#include "Innocent.h"

namespace TheTraitor {


	TheTraitor::Innocent::Innocent() : Role("Innocent") {

	}

	std::vector<SecretAction*> TheTraitor::Innocent::getSecretActions() {
		return std::vector<SecretAction*>{};
	}
}