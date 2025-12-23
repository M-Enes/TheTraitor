#pragma once

#include "Action.h"

namespace TheTraitor {
	class HealthAid : public virtual Action {
	public:
		HealthAid();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}