#pragma once

#include "Client/BridgeTypes.h"
#include "Common/GameState.h"
#include <SFML/Graphics.hpp>

namespace TheTraitor {

	class IGamePhase {
	public:
		virtual ~IGamePhase() = default;

		virtual void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) = 0;
		virtual const ViewData& handleInput(const InputData& inputData) = 0;
	};

}
