#pragma once

#include "ActionPacket.h"

namespace TheTraitor {
	enum class GameState {
		NONE,
		MENU,
		LOBBY,
		DISCUSSION_PHASE,
		ACTION_PHASE,
		RESOLUTION_PHASE,
		GAMEOVER,
		WIN
	};

	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		GameState gotoState;
		std::string enteredPlayerName;
	};

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
		bool isKeyEntered;
		char keyEntered;
	};
}