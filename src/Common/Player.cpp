#include <iostream>
#include <ctime>
#include <random>

#include "Player.h"

namespace TheTraitor {



	static int idBase = 0;


	Player::Player(std::string name, Country* country) : country(country), avatarID(-1) {
		this->name = name;

		// Generating a random number
		if (idBase == 0) {
			std::srand(std::time(nullptr));
			idBase = std::rand() % 100000;
			idBase = idBase < 0 ? -idBase : idBase;
		}

		this->playerID = idBase++;

	}

	Player::Player(std::string name, Country* country, int avatarID) : country(country), avatarID(avatarID) {
		this->name = name;

		// Generating a random number
		if (idBase == 0) {
			std::srand(std::time(nullptr));
			idBase = std::rand() % 100000;
		}

		this->playerID = idBase++;

	}

	// Default Constructor
	Player::Player() : avatarID(-1) {
		this->name = "Unnamed Player";
		this->country = new Country();

		// Generating a random number
		if (idBase == 0) {
			std::srand(std::time(nullptr));
			idBase = std::rand() % 100000;
		}

		this->playerID = idBase++;
	}

	// Name
	void Player::setName(std::string name) {
		this->name = name;
	}

	std::string Player::getName() const {
		return this->name;
	}

	// Country
	void Player::setCountry(Country* country) {
		this->country = country;
	}

	Country* Player::getCountry() const {
		return this->country;
	}

	// Role
	void Player::setRole(Role* role) {
		this->role = role;
	}

	void Player::updateCountryStat(CountryStatType stat, int value) {
		int currentValue;
		switch (stat) {
		case CountryStatType::Economy:
			currentValue = this->country->getEconomy();
			this->country->setEconomy(currentValue + value);
			break;
		case CountryStatType::Education:
			currentValue = this->country->getEducation();
			this->country->setEducation(currentValue + value);
			break;
		case CountryStatType::Health:
			currentValue = this->country->getHealth();
			this->country->setHealth(currentValue + value);
			break;
		default:
			break;
		}
	}

	Role* Player::getRole() const {
		return this->role;
	}

	void Player::setSocket(sf::TcpSocket* socket) {
		this->socket = socket;
	}

	sf::TcpSocket* Player::getSocket() const {
		return this->socket;
	}

	int Player::getPlayerID() const {
		return this->playerID;
	}

}
	
void TheTraitor::Player::setAvatarID(int id) {
	this->avatarID = id;
}

int TheTraitor::Player::getAvatarID() const {
	return this->avatarID;
}