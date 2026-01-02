#pragma once

#include "Common/ActionPacket.h"
#include "Common/GameState.h"
#include "Common/Country.h"

namespace TheTraitor {
	
	/**
	 * @brief Struct holding data for the View layer to render or process.
	 */
	struct ViewData {
		bool isActionRequested;          ///< Flag indicating if an action is requested.
		ActionType actionType;           ///< The type of action requested.
		CountryType actionTargetCountryType; ///< The target country type for the action.
		GamePhase gotoState;             ///< The game phase to transition to.
		std::string enteredPlayerName;   ///< The player name entered in the UI.
		int avatarID;                    ///< The selected avatar ID.
		bool isReady;                    ///< Flag indicating if the player is ready.
	};

	/**
	 * @brief Struct holding input data from the user.
	 */
	struct InputData {
		bool isMouseClicked;       ///< Flag indicating if the mouse was clicked.
		sf::Vector2i mousePosition; ///< The position of the mouse click.
		bool isKeyEntered;         ///< Flag indicating if a key was entered.
		char keyEntered;           ///< The character of the key entered.
	};
}