#pragma once

#include <cstdbool>

namespace TheTraitor {
	enum class CountryType {
		AMERICA, // 0
		AFRICA,  // 1
		ASIA,    // 2
		AUSTRALIA, // 3
		EUROPE,   // 4
		NONE
	};
	class Country {
	public:

		Country(int economy, int health, int education, CountryType type = CountryType::NONE);
		Country();
		int getEconomy() const;
		int getHealth() const;
		int getEducation() const;
		CountryType getType() const;
		
		bool isDestroyed() const;
		void checkDestroyed();
		void setDestroyed(bool destroyed);

		void setEconomy(int economy);
		void setHealth(int health);
		void setEducation(int education);
		void setType(CountryType type);
		
	private:
		int economy;
		int health;
		int education;
		bool destroyed;
		CountryType type;
	};
} 