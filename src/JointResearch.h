#pragma once

#include "Action.h"

namespace TheTraitor {
	class JointResearch : public virtual Action {
	public:
		JointResearch();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}