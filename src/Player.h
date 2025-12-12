#pragma once

#include <string>
#include "Country.h"
#include "Role.h"

namespace TheTraitor {
	class Player {
	public:
		Player(std::string name, Country country);
	private:
		int playerID;
		std::string name;
		Country country;
		Role role;
	};
}