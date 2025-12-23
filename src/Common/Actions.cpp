#include "Actions.h"
#include "Player.h"

namespace TheTraitor {
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

	std::string TradePact::getLogMessage(const Player& player, const Player& target) const {
		return "Trade Pact between " + player.getName() + " and " + target.getName();
	}

	std::string TradeEmbargo::getLogMessage(const Player& player, const Player& target) const {
		return "Trade Embargo against " + target.getName() + " by " + player.getName();
	}

	std::string JointResearch::getLogMessage(const Player& player, const Player& target) const {
		return "Joint Research between " + player.getName() + " and " + target.getName();
	}

	std::string SpreadMisinfo::getLogMessage(const Player& player, const Player& target) const {
		return "Spread Misinformation from " + player.getName() + " to " + target.getName();
	}

	std::string HealthAid::getLogMessage(const Player& player, const Player& target) const {
		return "Health Aid from " + player.getName() + " to " + target.getName();
	}

	std::string PoisonResources::getLogMessage(const Player& player, const Player& target) const {
		return "Poison Resources in " + target.getName() + " by " + player.getName();
	}

	std::string SabotageFactory::getLogMessage(const Player& player, const Player& target) const {
		return "Sabotage Factory in " + target.getName() + " by " + player.getName();
	}

	std::string DestroySchool::getLogMessage(const Player& player, const Player& target) const {
		return "Destroy School in " + target.getName() + " by " + player.getName();
	}

	std::string SpreadPlague::getLogMessage(const Player& player, const Player& target) const {
		return "Spread Plague in " + target.getName() + " by " + player.getName();
	}
}