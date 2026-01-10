#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <string>

namespace TheTraitor {

	class WinPhase : public IGamePhase {
	public:
		WinPhase(sf::RenderWindow& window, sf::Font& font);

		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		ViewData viewData;

		sf::Text title;
		sf::Text totalRoundsLabel;
		sf::Text totalTimeLabel;
		sf::Text traitorInfoLabel;
		Button quitGameButton;

		void resetViewData();
	};

}
