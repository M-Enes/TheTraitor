#pragma once

#include <string>
#include <SFML/Network.hpp>

#include "Country.h"

namespace TheTraitor {
	class Role;

	class Player {
	public:
		Player(std::string name, Country* country);
		Player();
		// Name
		void setName(std::string name);
		std::string getName() const;
		// Country
		void setCountry(Country* country);
		Country* getCountry() const;
		// Role
		void setRole(Role* role);
		Role* getRole() const;
		void setSocket(sf::TcpSocket* socket);
		sf::TcpSocket* getSocket() const;

	private:
		int playerID;
		std::string name;
		Country* country;
		Role* role;
		sf::TcpSocket* socket;
	};
}