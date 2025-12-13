#include "GameView.h"

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window) :
		window(window),
		viewData{ false, ActionType::TradePact, GameState::NONE },
		font("assets/fonts/CascadiaMono.ttf"),
		joinGameButton(sf::Vector2f(800, 600), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window),
		playerNameLabel(font),
		playerNameTextBox(font),
		playerNameTextBoxString("")
	{
		playerNameLabel.setPosition(sf::Vector2f(600, 500));
		playerNameLabel.setString("Player name");

		playerNameTextBox.setPosition(sf::Vector2f(600, 300));
		playerNameTextBox.setString(playerNameTextBoxString);
	}

	void GameView::renderMenu()
	{
		window.draw(playerNameLabel);
		window.draw(playerNameTextBox);
		joinGameButton.render();
	}

	void GameView::renderLobby(int playerCount)
	{
		sf::Text playerCountText(font);
		playerCountText.setString("Players joined: " + std::to_string(playerCount));
		playerCountText.setCharacterSize(24);
		playerCountText.setFillColor(sf::Color::White);
		playerCountText.setPosition(sf::Vector2f(100, 100));
		window.draw(playerCountText);
	}

	void GameView::renderPlay()
	{
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
			viewData.gotoState = GameState::LOBBY;
		}

		if (inputData.isKeyEntered) {
			char key = inputData.keyEntered;
			if (key == 8) { // Backspace
				if (!playerNameTextBoxString.empty()) {
					playerNameTextBoxString.pop_back();
				}
			}
			else if (key == 13) { // Enter

			}
			else {
				if (playerNameTextBoxString.size() < playerNameCharLimit) {
					playerNameTextBoxString += key;
				}
			}
			playerNameTextBox.setString(playerNameTextBoxString);
		}

		return viewData;
	}
}
