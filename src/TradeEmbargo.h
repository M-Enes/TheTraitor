#pragma once

#include "Action.h"

namespace TheTraitor {
	class TradeEmbargo : public virtual Action {
	public:
		TradeEmbargo();
		virtual execute(const Player& player1, const Player& player2) override;
		virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
	};
}