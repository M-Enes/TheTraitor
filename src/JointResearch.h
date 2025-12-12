#pragma once

#include "Action.h"

namespace TheTraitor {
	class JointResearch : public virtual Action {
	public:
		JointResearch();
		virtual execute(const Player& player1, const Player& player2) override;
		virtual std::string getLogMessage(const Player& player1, const Player& player2) override;
	};
}