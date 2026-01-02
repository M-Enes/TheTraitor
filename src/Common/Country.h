#pragma once

#include <cstdbool>

namespace TheTraitor {
	/**
	 * @brief Enumeration of available countries (continents) in the game.
	 */
	enum class CountryType {
		AMERICA,   ///< North and South America.
		AFRICA,    ///< Africa.
		ASIA,      ///< Asia.
		AUSTRALIA, ///< Australia/Oceania.
		EUROPE,    ///< Europe.
		NONE       ///< Represents no country or invalid country.
	};

	/**
	 * @brief Class representing a country with its statistics.
	 */
	class Country {
	public:

		/**
		 * @brief Constructor for Country.
		 * @param economy Initial economy stat.
		 * @param health Initial health stat.
		 * @param education Initial education stat.
		 * @param type The type (continent) of the country.
		 */
		Country(int economy, int health, int education, CountryType type = CountryType::NONE);

		/**
		 * @brief Default constructor.
		 */
		Country();

		/**
		 * @brief Gets the economy stat.
		 * @return The economy value.
		 */
		int getEconomy() const;

		/**
		 * @brief Gets the health stat.
		 * @return The health value.
		 */
		int getHealth() const;

		/**
		 * @brief Gets the education stat.
		 * @return The education value.
		 */
		int getEducation() const;

		/**
		 * @brief Gets the type of the country.
		 * @return The CountryType enum value.
		 */
		CountryType getType() const;
		
		/**
		 * @brief Checks if the country is destroyed.
		 * @return True if destroyed, false otherwise.
		 */
		bool isDestroyed() const;

		/**
		 * @brief Checks and updates the destroyed status based on stats.
		 * Usually called when stats change to see if any reached 0.
		 */
		void checkDestroyed();

		/**
		 * @brief Sets the destroyed status of the country.
		 * @param destroyed Boolean value indicating destroyed status.
		 */
		void setDestroyed(bool destroyed);

		/**
		 * @brief Sets the economy stat.
		 * @param economy The new economy value.
		 */
		void setEconomy(int economy);

		/**
		 * @brief Sets the health stat.
		 * @param health The new health value.
		 */
		void setHealth(int health);

		/**
		 * @brief Sets the education stat.
		 * @param education The new education value.
		 */
		void setEducation(int education);

		/**
		 * @brief Sets the type of the country.
		 * @param type The new CountryType.
		 */
		void setType(CountryType type);
		
	private:
		int economy;
		int health;
		int education;
		bool destroyed;
		CountryType type;
	};
} 