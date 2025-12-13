#include "GameView.h"

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window) :
		window(window),
		viewData{ false, ActionType::TradePact, GameState::NONE, "" },
		font("assets/fonts/CascadiaMono.ttf"),
		joinGameButton(sf::Vector2f(800, 600), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window),
		playerNameInputLabel(font),
		playerNameInputTextBox(font),
		playerNameInputTextBoxString(""),
		playerLabels({ font,font,font,font,font }),
		mapSprite(mapTexture)
 {
		if (!mapTexture.loadFromFile("assets/textures/map.jpg")) {
			// Handle error
		}


		playerNameLabel.setPosition(sf::Vector2f(600, 500));
		playerNameLabel.setString("Player name");
	{

		sf::Vector2f labelPosition(100, 200);
		for (auto& label : playerLabels) {
			label.setPosition(labelPosition);
			labelPosition += {0, 100};
		}

		playerNameInputLabel.setPosition(sf::Vector2f(600, 500));
		playerNameInputLabel.setString("Player name");

		playerNameInputTextBox.setPosition(sf::Vector2f(600, 300));
		playerNameInputTextBox.setString(playerNameInputTextBoxString);
	}

	void GameView::renderMenu()
	{
		window.draw(playerNameInputLabel);
		window.draw(playerNameInputTextBox);
		joinGameButton.render();
	}

	void GameView::renderLobby(const std::vector<std::string>& playerNames)
	{
		sf::Text playerCountText(font);
		playerCountText.setString("Players joined: " + std::to_string(playerNames.size()));
		playerCountText.setCharacterSize(24);
		playerCountText.setFillColor(sf::Color::White);
		playerCountText.setPosition(sf::Vector2f(100, 100));

		int i = 0;
		for (auto& label : playerLabels) {
			if (playerNames.size() <= i) {
				label.setString("Waiting for player...");
			}
			else {
				label.setString(playerNames[i]);
			}
			window.draw(label);
			i++;
		}

		window.draw(playerCountText);
	}

	// draw the game map
	void GameView::renderPlay()
	{
		window.draw(mapSprite);
	}

	void GameView::renderGameover()
	{
	}

	void GameView::renderWin()
	{
	}

	const ViewData& GameView::handleInput(const InputData& inputData) {
		viewData.isActionRequested = false;
		viewData.gotoState = GameState::NONE;

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isHovered = joinGameButton.isMouseOver(position);
		joinGameButton.updateHoverEffect(isHovered);

		if (inputData.isMouseClicked && isHovered) {
			viewData.enteredPlayerName = playerNameInputTextBoxString;
			viewData.gotoState = GameState::LOBBY;
		}

		if (inputData.isKeyEntered) {
			char key = inputData.keyEntered;
			if (key == 8) { // Backspace
				if (!playerNameInputTextBoxString.empty()) {
					playerNameInputTextBoxString.pop_back();
				}
			}
			else if (key == 13) { // Enter

			}
			else {
				if (playerNameInputTextBoxString.size() < playerNameCharLimit) {
					playerNameInputTextBoxString += key;
				}
			}
			playerNameInputTextBox.setString(playerNameInputTextBoxString);
		}

		return viewData;
	}
}
