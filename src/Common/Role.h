#pragma once

#include <string>
#include <vector>

namespace TheTraitor {
	class Action;
	class SecretAction;

	/**
	 * @brief Abstract base class representing a player's role.
	 */
	class Role {
	public:
		Role() = delete;
		
		/**
		 * @brief Virtual destructor.
		 */
		virtual ~Role() = default;

		/**
		 * @brief Gets the name of the role.
		 * @return The name string.
		 */
		std::string getName() const;

		/**
		 * @brief Gets the list of public actions available to this role.
		 * @return Vector of pointers to Action objects.
		 */
		std::vector<Action*> getPublicActions() const;

		/**
		 * @brief Gets the list of secret actions available to this role.
		 * @return Vector of pointers to SecretAction objects.
		 */
		virtual std::vector<SecretAction*> getSecretActions() const = 0;
	protected:
		/**
		 * @brief Protected constructor for Role.
		 * @param name The name of the role.
		 */
		Role(std::string name);
	private:
		std::string name;
	};

	/**
	 * @brief Class representing the Traitor role.
	 */
	class Traitor : public Role {
	public:
		/**
		 * @brief Constructor for Traitor role.
		 */
		Traitor();

		/**
		 * @brief Gets the secret actions available to the Traitor.
		 * @return Vector of pointers to SecretAction objects.
		 */
		std::vector<SecretAction*> getSecretActions() const override;
	};

	/**
	 * @brief Class representing the Innocent role.
	 */
	class Innocent : public Role {
	public:
		/**
		 * @brief Constructor for Innocent role.
		 */
		Innocent();

		/**
		 * @brief Gets the secret actions available to the Innocent (usually none).
		 * @return Vector of pointers to SecretAction objects.
		 */
		std::vector<SecretAction*> getSecretActions() const override;
	};
}