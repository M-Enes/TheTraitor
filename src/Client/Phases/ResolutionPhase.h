#pragma once

#include "IGamePhase.h"
#include <vector>

namespace TheTraitor {

	class ResolutionPhase : public IGamePhase {
	public:
		ResolutionPhase();

		void render(const GameState& gameState, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		ViewData viewData;
		void resetViewData();
	};

}
