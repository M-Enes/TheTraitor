#pragma once

#include <string>

namespace TheTraitor {
	class Player;

	/**
	 * @brief Enumeration of country statistics that can be affected by actions.
	 */
	enum class CountryStatType {
		Economy,    ///< Represents the economy stat.
		Education,  ///< Represents the education stat.
		Health      ///< Represents the health stat.
	};

	/**
	 * @brief Abstract base class for all actions in the game.
	 */
	class Action {
	public:
		/**
		 * @brief Virtual destructor.
		 */
		virtual ~Action() = default;

		/**
		 * @brief Executes the action, modifying the player's and target's stats.
		 * @param player The player performing the action.
		 * @param target The target player of the action.
		 */
		void execute(Player& player, Player& target) const;

		/**
		 * @brief Gets the log message describing the action result.
		 * @param player The player who performed the action.
		 * @param target The target of the action.
		 * @return A string containing the log message.
		 */
		virtual std::string getLogMessage(const Player& player, const Player& target) const = 0;

		/**
		 * @brief Gets the effect of the action on the initiating player.
		 * @return The integer value of the effect.
		 */
		int getEffectToPlayer() const;

		/**
		 * @brief Gets the effect of the action on the target player.
		 * @return The integer value of the effect.
		 */
		int getEffectToTarget() const;

		/**
		 * @brief Gets the type of statistic affected by this action.
		 * @return The CountryStatType enum value.
		 */
		CountryStatType getEffectedStatType() const;

	protected:
		/**
		 * @brief Constructor for the Action class.
		 * @param effectPlayer Effect on the source player's stat.
		 * @param effectTarget Effect on the target player's stat.
		 * @param type The type of stat affected.
		 */
		Action(int effectPlayer, int effectTarget, CountryStatType type);

	private:
		int effectToPlayer;
		int effectToTarget;
		CountryStatType effectedStatType;
	};

	/**
	 * @brief Abstract base class for secret actions (actions performed by the Traitor).
	 */
	class SecretAction : public virtual Action {
	public:
		virtual ~SecretAction() = default;
	protected:
		SecretAction(int effectPlayer, int effectTarget, CountryStatType type);
	};

	/**
	 * @brief Represents a Trade Pact action.
	 */
	class TradePact : public virtual Action {
	public:
		TradePact();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Trade Embargo action.
	 */
	class TradeEmbargo : public virtual Action {
	public:
		TradeEmbargo();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Joint Research action.
	 */
	class JointResearch : public virtual Action {
	public:
		JointResearch();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Spread Misinformation action.
	 */
	class SpreadMisinfo : public virtual Action {
	public:
		SpreadMisinfo();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Health Aid action.
	 */
	class HealthAid : public virtual Action {
	public:
		HealthAid();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Poison Resources action (Secret).
	 */
	class PoisonResources : public virtual Action {
	public:
		PoisonResources();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Sabotage Factory action (Secret).
	 */
	class SabotageFactory : public virtual SecretAction {
	public:
		SabotageFactory();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Destroy School action (Secret).
	 */
	class DestroySchool : public virtual SecretAction {
	public:
		DestroySchool();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	/**
	 * @brief Represents a Spread Plague action (Secret).
	 */
	class SpreadPlague : public virtual SecretAction {
	public:
		SpreadPlague();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};
}