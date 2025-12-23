#pragma once

#include "SecretAction.h"

namespace TheTraitor {
	class SabotageFactory : public virtual SecretAction {
	public:
		SabotageFactory();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}