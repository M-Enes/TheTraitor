#pragma once

#include "Action.h"

namespace TheTraitor {
	class TradeEmbargo : public virtual Action {
	public:
		TradeEmbargo();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}