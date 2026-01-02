#pragma once

#include "Client/Phases/IGamePhase.h"
#include <vector>
#include <array>
#include <string>

namespace TheTraitor {

	class LobbyPhase : public IGamePhase {
	public:
		LobbyPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);

		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;
		ViewData viewData;

		std::array<sf::Text, 5> playerLabels;

		void resetViewData();
	};

}
