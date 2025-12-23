#include "Actions.h"
#include "Player.h"

namespace TheTraitor {
	void Action::execute(Player& player, Player& target) const {
		player.updateCountryStat(effectedStatType, effectToPlayer);
		target.updateCountryStat(effectedStatType, effectToTarget);
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
}