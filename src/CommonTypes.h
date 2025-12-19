#pragma once

#include "ActionPacket.h"
#include "GameState.h"

namespace TheTraitor {
	
	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		GamePhase gotoState;
		std::string enteredPlayerName;
	};

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
		bool isKeyEntered;
		char keyEntered;
	};
}