#include <iostream>
#include "Country.h"

namespace TheTraitor {

	Country::Country(int economy, int health, int education, CountryType type) {
		this->economy = economy;
		this->health = health;
		this->education = education;
		this->destroyed = false;
		this->type = type;
	}


	Country::Country() {
		this->economy = 0;
		this->health = 0;
		this->education = 0;
		this->destroyed = false;
		this->type = CountryType::NONE;
	}

	CountryType Country::getType() const {
		return this->type;
	}

	void Country::setType(CountryType type) {
		this->type = type;
	}

	int Country::getEconomy() const {
		return this->economy;
	}

	int Country::getHealth() const {
		return this->health;
	}

	int Country::getEducation() const {
		return this->education;
	}

	bool Country::isDestroyed() const {
		return this->destroyed;
	}

	void Country::setEconomy(int economy) {
		if (economy < 0) {
			economy = 0;
		}
		else if (economy > 100) {
			economy = 100;
		}
		this->economy = economy;
	}

	void Country::setHealth(int health) {
		if (health < 0) {
			health = 0;
		}
		else if (health > 100) {
			health = 100;
		}
		this->health = health;
	}

	void Country::setEducation(int education) {
		if (education < 0) {
			education = 0;
		}
		else if (education > 100) {
			education = 100;
		}
		this->education = education;
	}


	void Country::checkDestroyed() {
		// Destroyed if any stat reaches 0
		// Maybe change this condition later
		if (economy == 0 || health == 0 || education == 0) {
			destroyed = true;
		}
		else {
			destroyed = false;
		}
	}

	void Country::setDestroyed(bool destroyed) {
		this->destroyed = destroyed;
	}
}