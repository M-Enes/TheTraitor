#include "Client/Phases/DiscussionPhase.h"

namespace TheTraitor {

	DiscussionPhase::DiscussionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath) 
		: window(window), font(font), avatarTextures(avatarTextures), 
		  viewData{ false, ActionType::TradePact, CountryType::NONE, NONE, "", 0, false},
		  readyButton(sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y - 100), sf::Vector2f(200, 60), sf::Vector2f(10, 10), "Ready", font, window, 30, sf::Color::Black, sf::Color::White, 5, sf::Color(100,100,100), sf::Color::White),
		  isReady(false),
		  titleLabel(font, "Discussion Phase", 40),
		  timerLabel(font, "00:00", 30),
		  playerInfo({font, font, font, font}),
		  countryNormalColor(sf::Color::Green),
		  countryHoverColor(sf::Color(0, 200, 0)),
		  countrySelectedColor(sf::Color::Red),
		  economyIconTexture(executableFolderPath + "/assets/icons/icons8-cash-64.png"),
		  healthIconTexture(executableFolderPath + "/assets/icons/icons8-medical-kit-64.png"),
		  educationIconTexture(executableFolderPath + "/assets/icons/icons8-book-64.png"),
		  economyIconSprite(economyIconTexture),
		  healthIconSprite(healthIconTexture),
		  educationIconSprite(educationIconTexture)
	{
		titleLabel.setPosition({ 50, 30 });
		titleLabel.setStyle(sf::Text::Bold);
		
		timerLabel.setPosition({ (float)window.getSize().x - 150, 30 });
	}

	void DiscussionPhase::render(const GameState& gameState, int localPlayerID, float elapsedTime, int roundCounter) {
		window.draw(titleLabel);

		int remainingSeconds = 120 - (int)elapsedTime;
		if (remainingSeconds < 0) remainingSeconds = 0;
		timerLabel.setString(std::to_string(remainingSeconds / 60) + ":" + ((remainingSeconds % 60 < 10) ? "0" : "") + std::to_string(remainingSeconds % 60));
		window.draw(timerLabel);
		
		readyButton.render();

		// Render Player Infos
		int posY = 100;

		for (const auto& player : gameState.players) {
			auto& [name, economy, health, education] = playerInfo;

			std::string displayName = player.getName();
			if (player.getPlayerID() == localPlayerID) {
				displayName += " (You)";
			}

			// We put them in a column on the right side, similar to Action Phase but maybe simpler
			float rightColumnX = (float)window.getSize().x - 550;
			
			// Name
			name.setString(displayName);
			name.setCharacterSize(30);
			name.setPosition({ rightColumnX, (float)posY });
			
			// Use simple layout: Icon Value Icon Value ...
			// Economy
			economyIconSprite.setPosition({ rightColumnX, (float)posY + 40 });
			economy.setString(std::to_string(player.getCountry()->getEconomy()));
			economy.setCharacterSize(25);
			economy.setPosition({ rightColumnX + 70, (float)posY + 55 }); 

			// Health
			healthIconSprite.setPosition({ rightColumnX + 140, (float)posY + 40 });
			health.setString(std::to_string(player.getCountry()->getHealth()));
			health.setCharacterSize(25);
			health.setPosition({ rightColumnX + 210, (float)posY + 55 });

			// Education
			educationIconSprite.setPosition({ rightColumnX + 280, (float)posY + 45 });
			education.setString(std::to_string(player.getCountry()->getEducation()));
			education.setCharacterSize(25);
			education.setPosition({ rightColumnX + 350, (float)posY + 55 });

			// Avatar
			int avatarID = player.getAvatarID();
			if (avatarID >= 0 && avatarID < static_cast<int>(avatarTextures.size())) {
				sf::Sprite avatarSprite(avatarTextures[avatarID]);
				float size = 50.0f; 
				sf::Vector2u texSize = avatarTextures[avatarID].getSize();
				if (texSize.x > 0 && texSize.y > 0) {
					avatarSprite.setScale({ size / texSize.x, size / texSize.y });
				}
				avatarSprite.setPosition({ rightColumnX - 60, (float)posY + 30 });
				window.draw(avatarSprite);
			}

			window.draw(name);
			window.draw(economy);
			window.draw(health);
			window.draw(education);
			window.draw(economyIconSprite);
			window.draw(healthIconSprite);
			window.draw(educationIconSprite);

			posY += 120; // Spacing
		}
	}

	const ViewData& DiscussionPhase::handleInput(const InputData& inputData) {
		resetViewData();
		
		sf::Vector2f mousePos = window.mapPixelToCoords(inputData.mousePosition);
		bool isHovered = readyButton.isMouseOver(mousePos);
		readyButton.updateHoverEffect(isHovered);

		if (inputData.isMouseClicked && isHovered && !isReady) {
			isReady = true;
			viewData.isReady = true;
			readyButton.setDisabled(true);
			readyButton.setLabelString("Waiting...");
		}
		
		if (!(inputData.isMouseClicked && isHovered) && !isReady) {
			viewData.isReady = false;
			readyButton.setDisabled(false);
			readyButton.setLabelString("Ready");
		}

		return viewData;
	}

	void DiscussionPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
		viewData.isReady = false; 
	}

}
