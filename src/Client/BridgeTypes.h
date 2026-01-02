#pragma once

#include "Common/ActionPacket.h"
#include "Common/GameState.h"
#include "Common/Country.h"

namespace TheTraitor {
	
	struct ViewData {
		bool isActionRequested;
		ActionType actionType;
		CountryType actionTargetCountryType;
		GamePhase gotoState;
		std::string enteredPlayerName;
		int avatarID;
		bool isReady;
	};

	struct InputData {
		bool isMouseClicked;
		sf::Vector2i mousePosition;
		bool isKeyEntered;
		char keyEntered;
	};
}