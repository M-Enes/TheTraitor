#pragma once

#include "SecretAction.h"

namespace TheTraitor {
	class SpreadPlague : public SecretAction {
	public:
		SpreadPlague();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}