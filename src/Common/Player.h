#pragma once

#include <string>
#include <SFML/Network.hpp>

#include "Country.h"
#include "Actions.h"

namespace TheTraitor {
	class Role;
	
	/**
	 * @brief Class representing a player in the game.
	 */
	class Player {
	public:
		/**
		 * @brief Constructor for Player.
		 * @param name The name of the player.
		 * @param country Pointer to the country assigned to the player.
		 */
		Player(std::string name, Country* country);

		/**
		 * @brief Constructor for Player with avatar ID.
		 * @param name The name of the player.
		 * @param country Pointer to the country assigned to the player.
		 * @param avatarID The ID of the avatar image.
		 */
		Player(std::string name, Country* country, int avatarID);

		/**
		 * @brief Default constructor.
		 */
		Player();
		
		/**
		 * @brief Sets the player's name.
		 * @param name The new name string.
		 */
		void setName(std::string name);

		/**
		 * @brief Gets the player's name.
		 * @return The name string.
		 */
		std::string getName() const;
		
		/**
		 * @brief Sets the player's country.
		 * @param country Pointer to the Country object.
		 */
		void setCountry(Country* country);

		/**
		 * @brief Gets the player's country.
		 * @return Pointer to the Country object.
		 */
		Country* getCountry() const;
		
		/**
		 * @brief Sets the player's role (Innocent or Traitor).
		 * @param role Pointer to the Role object.
		 */
		void setRole(Role* role);

		/**
		 * @brief Gets the player's role.
		 * @return Pointer to the Role object.
		 */
		Role* getRole() const;

		/**
		 * @brief Sets the network socket for the player (Server only).
		 * @param socket Pointer to the SFML TcpSocket.
		 */
		void setSocket(sf::TcpSocket* socket);

		/**
		 * @brief Gets the network socket for the player (Server only).
		 * @return Pointer to the SFML TcpSocket.
		 */
		sf::TcpSocket* getSocket() const;

		/**
		 * @brief Gets the unique player ID.
		 * @return The integer player ID.
		 */
		int getPlayerID() const;

		/**
		 * @brief Updates the player's state.
		 */
		void updatePlayer();

		/**
		 * @brief Updates a specific statistic of the player's country.
		 * @param stat The type of statistic to update.
		 * @param value The amount to add (can be negative).
		 */
		void updateCountryStat(CountryStatType stat, int value);

		/**
		 * @brief Sets the avatar ID for the player.
		 * @param id The new avatar ID.
		 */
		void setAvatarID(int id);

		/**
		 * @brief Gets the avatar ID of the player.
		 * @return The avatar ID.
		 */
		int getAvatarID() const;

		/**
		 * @brief Sets the player ID manually.
		 * @param id The new player ID.
		 */
		void setPlayerID(int id);

	private:
		int playerID;
		int avatarID;
		std::string name;
		Country* country;
		Role* role;
		sf::TcpSocket* socket;
	};
}