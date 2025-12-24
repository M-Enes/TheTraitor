#pragma once

#include "Common/ActionPacket.h"
#include "Common/GameState.h"

namespace TheTraitor {
	
	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		int actionTargetID;
		GamePhase gotoState;
		std::string enteredPlayerName;
		int avatarID;
	};

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
		bool isKeyEntered;
		char keyEntered;
	};
}