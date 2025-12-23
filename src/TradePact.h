#pragma once

#include "Action.h"

namespace TheTraitor {
	class TradePact : public virtual Action {
	public:
		TradePact();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}