#pragma once

#include "Action.h"

namespace TheTraitor {
	class TradePact : public virtual Action {
	public:
		TradePact();
		virtual execute(const Player& player1, const Player& player2) override;
		virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
	};
}