#pragma once

#include <string>
#include "Player.h"

namespace TheTraitor {
	class Action {
	public:
		Action() = delete;
		virtual execute(const Player& player1, const Player& player2) = 0;
		virtual std::string getLogMessage(const Player& player1, const Player& player2) = 0;
	protected:
		Action();
	};
}