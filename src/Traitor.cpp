#include <iostream>

#include "Traitor.h"

namespace TheTraitor {

	Traitor::Traitor() : Role("Traitor") { //Çok object oriented oldu bu yaa :) oop güzeldir tadında olursa :D

	}

	std::vector<SecretAction*> Traitor::getSecretActions() {
		return std::vector<SecretAction*>{};
	}
}