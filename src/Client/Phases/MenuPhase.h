#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <vector>
#include <array>
#include <string>

namespace TheTraitor {

	class MenuPhase : public IGamePhase {
	public:
		MenuPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures);
		
		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		sf::RenderWindow& window;
		sf::Font& font;
		ViewData viewData;
		
		Button joinGameButton;
		sf::Text playerNameInputLabel;
		sf::Text playerNameInputTextBox;
		std::string playerNameInputTextBoxString;
		const unsigned long int playerNameCharLimit = 15;

		// Avatar UI
		sf::Text avatarLabel;
		std::vector<sf::Sprite> avatarSprites;
		int currentSelectedAvatarIndex;

		sf::Text titleLabel;
		sf::Text howToPlayLabel;

		void resetViewData();
		void initAvatarSprites(const std::vector<sf::Texture>& avatarTextures);

		sf::Clock blinkClock;
		bool showCursor;
	};

}
