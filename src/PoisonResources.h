#pragma once

#include "Action.h"

namespace TheTraitor {
	class PoisonResources : public virtual Action {
	public:
		PoisonResources();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}