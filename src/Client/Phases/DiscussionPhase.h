#pragma once

#include "Client/Phases/IGamePhase.h"
#include <vector>

namespace TheTraitor {

	class DiscussionPhase : public IGamePhase {
	public:
		DiscussionPhase();

		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		ViewData viewData;
		void resetViewData();
	};

}
