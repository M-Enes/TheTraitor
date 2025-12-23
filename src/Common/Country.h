#pragma once

#include <cstdbool>

namespace TheTraitor {
	class Country {
	public:
		Country(int economy, int health, int education);
		Country();
		int getEconomy();
		int getHealth();
		int getEducation();
		bool isDestroyed();
		void setDestroyed();

		void setEconomy(int economy);
		void setHealth(int health);
		void setEducation(int education);
		void setDestroyed(bool destroyed);

	private:
		int economy;
		int health;
		int education;
		bool destroyed;
	};
} 