#pragma once

#include <string>

namespace TheTraitor {
	class Player;

	enum class CountryStatType {
		Economy,
		Education,
		Health
	};

	class Action {
	public:
		virtual ~Action() = default;
		void execute(Player& player, Player& target) const;
		virtual std::string getLogMessage(const Player& player, const Player& target) const = 0;
		int getEffectToPlayer() const;
		int getEffectToTarget() const;
		CountryStatType getEffectedStatType() const;
	protected:
		Action(int effectPlayer, int effectTarget, CountryStatType type);
	private:
		int effectToPlayer;
		int effectToTarget;
		CountryStatType effectedStatType;
	};

	class SecretAction : public virtual Action {
	public:
		virtual ~SecretAction() = default;
	protected:
		SecretAction(int effectPlayer, int effectTarget, CountryStatType type);
	};

	class TradePact : public virtual Action {
	public:
		TradePact();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class TradeEmbargo : public virtual Action {
	public:
		TradeEmbargo();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class JointResearch : public virtual Action {
	public:
		JointResearch();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class SpreadMisinfo : public virtual Action {
	public:
		SpreadMisinfo();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class HealthAid : public virtual Action {
	public:
		HealthAid();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class PoisonResources : public virtual Action {
	public:
		PoisonResources();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class SabotageFactory : public virtual SecretAction {
	public:
		SabotageFactory();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class DestroySchool : public virtual SecretAction {
	public:
		DestroySchool();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};

	class SpreadPlague : public virtual SecretAction {
	public:
		SpreadPlague();
		std::string getLogMessage(const Player& player, const Player& target) const override;
	};
}