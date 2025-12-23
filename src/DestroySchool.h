#pragma once

#include "SecretAction.h"

namespace TheTraitor {
	class DestroySchool : public virtual SecretAction {
	public:
		DestroySchool();
		void execute(Player* player1, Player* player2) override;
		std::string getLogMessage(Player* player1, Player* player2) override;
	};
}