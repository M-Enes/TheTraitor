#pragma once

namespace TheTraitor {
	class Country {
	public:
		Country(int economy, int health, int education);
		int getEconomy();
		int getHealth();
		int getEducation();
		bool isDestroyed();
		void setDestroyed();
	private:
		int economy;
		int health;
		int education;
		bool isDestroyed;
	};
} 