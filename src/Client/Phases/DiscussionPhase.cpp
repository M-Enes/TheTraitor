#include "Client/Phases/DiscussionPhase.h"

namespace TheTraitor {

	DiscussionPhase::DiscussionPhase() 
		: viewData{ false, ActionType::TradePact, CountryType(NONE), NONE, "", 0}
	{
	}

	void DiscussionPhase::render(const GameState& gameState, int localPlayerID, float elapsedTime, int roundCounter) {
	}

	const ViewData& DiscussionPhase::handleInput(const InputData& inputData) {
		resetViewData();
		return viewData;
	}

	void DiscussionPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

}
