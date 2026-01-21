#pragma once

#include "IGamePhase.h"
#include <vector>

namespace TheTraitor {

	class ResolutionPhase : public IGamePhase {
	public:
		ResolutionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);

		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

		void setActions(const std::vector<ActionPacket>& actions);

	private:
		ViewData viewData;
		void resetViewData();

		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;
		std::vector<ActionPacket> actions;

		std::string getActionName(ActionType type);
	};

}
