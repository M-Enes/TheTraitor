#pragma once

#include "ActionPacket.h"

namespace TheTraitor {
	enum class GameState {
		NONE,
		MENU,
		LOBBY,
		PLAY,
		GAMEOVER,
		WIN
	};

	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		GameState gotoState;
	};

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
		bool isKeyEntered;
		char keyEntered;
	};
}