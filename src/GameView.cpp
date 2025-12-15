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
		actionMenu({ 310, (float)window.getSize().y - 40 }),
		eventLogMenu({ 540, (float)window.getSize().y - 40 }),
		roundLabel(font, "Round 1"),
		timerLabel(font, "01:02"),
		eventLogString("MuhammedEnesKrc made Trade Pact with MuhammedEnesKrc\n\n"
			"MuhammedEnesKrc applied Trade Embargo to MuhammedEnesKrc"),
		eventLogLabel(font, eventLogString, 15)
	{

		actionMenu.setPosition({ 20, 20 });
		actionMenu.setFillColor(sf::Color::Black);
		actionMenu.setOutlineThickness(5);
		actionMenu.setOutlineColor(sf::Color::White);

		std::array<std::string, 9> actionMenuButtonStrings = {
			"Trade Pact",
			"Trade Embargo",
			"Joint Research",
			"Spread Misinfo",
			"Health Aid",
			"Poison Resources",
			"Sabotage Factory",
			"Destroy School",
			"Spread Plague"
		};

		float actionMenuButtonPositionY = 100;

		actionMenuButtons.reserve(actionMenuButtonStrings.size());
		for (const auto& buttonString : actionMenuButtonStrings) {
			actionMenuButtons.push_back({ buttonString ,{sf::Vector2f(50, actionMenuButtonPositionY), sf::Vector2f(240, 50), sf::Vector2f(10, 10), buttonString, font, window, 24, sf::Color::Black, sf::Color::White, 5, sf::Color::White} });
			actionMenuButtonPositionY += 100;
		}

		eventLogMenu.setPosition({ (float)window.getSize().x - 560,20 });
		eventLogMenu.setFillColor(sf::Color::Color(30, 30, 30));

		roundLabel.setPosition({ (float)window.getSize().x - 500, 20 });
		timerLabel.setPosition({ (float)window.getSize().x - 200, 20 });

		eventLogLabel.setPosition({ (float)window.getSize().x - 540, 80 });


		playerNameInputLabel.setPosition(sf::Vector2f(600, 500));
		playerNameInputLabel.setString("Player name");

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

	void GameView::renderDiscussionPhase()
	{
	}

	void GameView::renderActionPhase()
	{
		
		//sf::RectangleShape topbar({1880, 50});
		//topbar.setPosition({20, 0});



		window.draw(actionMenu);
		for (auto& buttonPair : actionMenuButtons) {
			buttonPair.second.render();
		}

		// TODO: add game map

		window.draw(eventLogMenu);
		window.draw(roundLabel);
		window.draw(timerLabel);
		window.draw(eventLogLabel);
		//window.draw(topbar);
	}

	void GameView::renderResolutionPhase()
	{
	}

	void GameView::renderGameover()
	{
	}

	void GameView::renderWin()
	{
	}

	const ViewData& GameView::handleMenuInput(const InputData& inputData) {
		resetViewData();

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
	const ViewData& GameView::handleLobbyInput(const InputData& inputData)
	{
		resetViewData();

		return viewData;
	}
	const ViewData& GameView::handleDiscussionPhaseInput(const InputData& inputData)
	{
		resetViewData();

		return viewData;
	}
	const ViewData& GameView::handleActionPhaseInput(const InputData& inputData)
	{
		resetViewData();

		return viewData;
	}

	const ViewData& GameView::handleResolutionPhaseInput(const InputData& inputData)
	{
		resetViewData();

		return viewData;
	}

	void GameView::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = GameState::NONE;
	}
}
