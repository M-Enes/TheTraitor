#pragma once

#include <string>
#include <SFML/Network.hpp>

#include "Country.h"
#include "Actions.h"

namespace TheTraitor {
	class Role;

	class Player {
	public:
		Player(std::string name, Country* country);
		Player(std::string name, Country* country, int avatarID);
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
		int getPlayerID() const;
		void updatePlayer();
		/* update value is relative e.g. +10, -10 .*/
		void updateCountryStat(CountryStatType stat, int value);
		void setAvatarID(int id);
		int getAvatarID() const;

	private:
		int playerID;
		int avatarID;
		std::string name;
		Country* country;
		Role* role;
		sf::TcpSocket* socket;
	};
}