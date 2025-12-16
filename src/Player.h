#pragma once

#include <string>
#include "Country.h"
#include "Role.h"

namespace TheTraitor {
	class Player {
	public:
		Player(std::string name, Country country);
		Player();
		// Name
		void setName(std::string name);
		std::string getName() const;
		// Country
		void setCountry(Country country);
		Country getCountry() const;
		// Role
		void setRole(Role* role);
		Role* getRole() const;

	private:
		int playerID;
		std::string name;
		Country country;
		Role* role;
	};
}