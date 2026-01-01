#include "Actions.h"
#include "Player.h"

namespace TheTraitor {
	Action::Action(int effectPlayer, int effectTarget, CountryStatType type)
		: effectToPlayer(effectPlayer), effectToTarget(effectTarget), effectedStatType(type) {}

	void Action::execute(Player& player, Player& target) const {
		player.updateCountryStat(effectedStatType, effectToPlayer);
		target.updateCountryStat(effectedStatType, effectToTarget);
		player.getCountry()->checkDestroyed();
		target.getCountry()->checkDestroyed();
	}

	int Action::getEffectToPlayer() const {
		return this->effectToPlayer;
	}

	int Action::getEffectToTarget() const {
		return this->effectToTarget;
	}

	CountryStatType Action::getEffectedStatType() const {
		return this->effectedStatType;
	}

	SecretAction::SecretAction(int effectPlayer, int effectTarget, CountryStatType type)
		: Action(effectPlayer, effectTarget, type) {}

	TradePact::TradePact() : Action(10, 10, CountryStatType::Economy) {}
	std::string TradePact::getLogMessage(const Player& player, const Player& target) const {
		return "Trade Pact between " + player.getName() + " and " + target.getName();
	}

	TradeEmbargo::TradeEmbargo() : Action(-10, -20, CountryStatType::Economy) {}
	std::string TradeEmbargo::getLogMessage(const Player& player, const Player& target) const {
		return "Trade Embargo against " + target.getName() + " by " + player.getName();
	}

	JointResearch::JointResearch() : Action(10, 10, CountryStatType::Education) {}
	std::string JointResearch::getLogMessage(const Player& player, const Player& target) const {
		return "Joint Research between " + player.getName() + " and " + target.getName();
	}

	SpreadMisinfo::SpreadMisinfo() : Action(-10, -20, CountryStatType::Education) {}
	std::string SpreadMisinfo::getLogMessage(const Player& player, const Player& target) const {
		return "Spread Misinformation from " + player.getName() + " to " + target.getName();
	}

	HealthAid::HealthAid() : Action(10, 10, CountryStatType::Health) {}
	std::string HealthAid::getLogMessage(const Player& player, const Player& target) const {
		return "Health Aid from " + player.getName() + " to " + target.getName();
	}

	PoisonResources::PoisonResources() : Action(-10, -20, CountryStatType::Health) {}
	std::string PoisonResources::getLogMessage(const Player& player, const Player& target) const {
		return "Poison Resources in " + target.getName() + " by " + player.getName();
	}

	SabotageFactory::SabotageFactory() : Action(0, -30, CountryStatType::Economy), SecretAction(0, -30, CountryStatType::Economy) {}
	std::string SabotageFactory::getLogMessage(const Player& player, const Player& target) const {
		return "Sabotage Factory in " + target.getName() + " by " + player.getName();
	}

	DestroySchool::DestroySchool() : Action(0, -30, CountryStatType::Education), SecretAction(0, -30, CountryStatType::Education) {}
	std::string DestroySchool::getLogMessage(const Player& player, const Player& target) const {
		return "Destroy School in " + target.getName() + " by " + player.getName();
	}

	SpreadPlague::SpreadPlague() : Action(0, -30, CountryStatType::Health), SecretAction(0, -30, CountryStatType::Health) {}
	std::string SpreadPlague::getLogMessage(const Player& player, const Player& target) const {
		return "Spread Plague in " + target.getName() + " by " + player.getName();
	}
}