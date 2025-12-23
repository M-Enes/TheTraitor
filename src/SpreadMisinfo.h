#pragma once

#include "Action.h"

namespace TheTraitor {
	class SpreadMisinfo : public virtual Action {
	public:
		SpreadMisinfo();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}