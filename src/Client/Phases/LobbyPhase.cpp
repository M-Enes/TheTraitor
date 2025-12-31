#include "Client/Phases/LobbyPhase.h"

namespace TheTraitor {

	LobbyPhase::LobbyPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures)
		: window(window), font(font), avatarTextures(avatarTextures),
		viewData{ false, ActionType::TradePact, 0, NONE, "", 0 },
		playerLabels({ font,font,font,font,font })
	{
		sf::Vector2f labelPosition(180, 200);
		for (auto& label : playerLabels) {
			label.setPosition(labelPosition);
			labelPosition += {0, 100};
		}
	}

	void LobbyPhase::render(const GameState& gameState, float elapsedTime, int roundCounter) {
		sf::Text playerCountText(font);
		playerCountText.setString("Players joined: " + std::to_string(gameState.players.size()));
		playerCountText.setCharacterSize(24);
		playerCountText.setFillColor(sf::Color::White);
		playerCountText.setPosition(sf::Vector2f(100, 100));

		long unsigned int i = 0;
		for (auto& label : playerLabels) {
			if (gameState.players.size() <= i) {
				label.setString("Waiting for player...");
			}
			else {
				label.setString(gameState.players[i].getName());

				// Draw Avatar
				int avatarID = gameState.players[i].getAvatarID();
				if (avatarID >= 0 && avatarID < static_cast<int>(avatarTextures.size())) {
					sf::Sprite avatarSprite(avatarTextures[avatarID]);
					float size = 50.0f;
					sf::Vector2u texSize = avatarTextures[avatarID].getSize();
					if (texSize.x > 0 && texSize.y > 0) {
						avatarSprite.setScale({ size / texSize.x, size / texSize.y });
					}

					sf::Vector2f pos = label.getPosition();
					avatarSprite.setPosition({ 100.0f, pos.y - 10.0f });
					window.draw(avatarSprite);
				}
			}
			window.draw(label);
			i++;
		}

		window.draw(playerCountText);
	}

	const ViewData& LobbyPhase::handleInput(const InputData& inputData) {
		resetViewData();
		return viewData;
	}

	void LobbyPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

}
