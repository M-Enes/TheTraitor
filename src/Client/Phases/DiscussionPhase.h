#pragma once

#include "Client/Phases/IGamePhase.h"
#include "Client/Button.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace TheTraitor {

	class DiscussionPhase : public IGamePhase {
	public:
		DiscussionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath);

		void render(const GameState& gameState, int localPlayerID, float elapsedTime = 0, int roundCounter = 0) override;
		const ViewData& handleInput(const InputData& inputData) override;

	private:
		ViewData viewData;
		void resetViewData();

		sf::RenderWindow& window;
		sf::Font& font;
		const std::vector<sf::Texture>& avatarTextures;

		Button readyButton;
		bool isReady;

		// UI Elements
		sf::Text titleLabel;
		sf::Text timerLabel;
		
		// Player Info Elements (Reused logic from ActionPhase)
		struct PlayerInfoUI {
			sf::Text name;
			sf::Text economy;
			sf::Text health;
			sf::Text education;
		} playerInfo;


		sf::Texture economyIconTexture;
		sf::Texture healthIconTexture;
		sf::Texture educationIconTexture;

		sf::Sprite economyIconSprite;
		sf::Sprite healthIconSprite;
		sf::Sprite educationIconSprite;

		sf::Color countryNormalColor;
		sf::Color countryHoverColor; // Not used for map interaction here but maybe for highlighting?
		sf::Color countrySelectedColor;
		
		int currentRound = 0;
	};

}
