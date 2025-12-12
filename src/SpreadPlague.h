#pragma once

#include "SecretAction.h"

namespace TheTraitor {
	class SpreadPlague : public virtual SecretAction {
	public:
		SpreadPlague();
		virtual execute(const Player& player1, const Player& player2) override;
		virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
	};
}