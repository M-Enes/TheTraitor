#include "Client/Phases/ResolutionPhase.h"

namespace TheTraitor {

	ResolutionPhase::ResolutionPhase() 
		: viewData{ false, ActionType::TradePact, 0, NONE, "", 0 }
	{
	}

	void ResolutionPhase::render(const GameState& gameState, float elapsedTime, int roundCounter) {
	}

	const ViewData& ResolutionPhase::handleInput(const InputData& inputData) {
		resetViewData();
		return viewData;
	}

	void ResolutionPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

}
