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
		mapTexture("assets/textures/map.jpg"),
		mapSprite(mapTexture)
	{

		playerNameInputLabel.setPosition(sf::Vector2f(600, 500));
		playerNameInputLabel.setString("Player name");
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

<<<<<<< Updated upstream
	// draw the game map
	void GameView::renderPlay()
	{
		window.draw(mapSprite);
=======
	void GameView::renderDiscussionPhase()
	{
		drawMap();
	}

	void GameView::renderActionPhase()
	{
		
		//sf::RectangleShape topbar({1880, 50});
		//topbar.setPosition({20, 0});



		window.draw(actionMenu);
		for (auto& buttonPair : actionMenuButtons) {
			buttonPair.second.render();
		}

		drawMap();

		window.draw(eventLogMenu);
		window.draw(roundLabel);
		window.draw(timerLabel);
		window.draw(eventLogLabel);
		//window.draw(topbar);
	}

	void GameView::renderResolutionPhase()
	{
		drawMap();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
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

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);


		bool isHovered;
		for (auto& [name, button] : actionMenuButtons) {
			isHovered = false;
			isHovered = button.isMouseOver(position);

			button.updateHoverEffect(isHovered);

			if (inputData.isMouseClicked && isHovered) {
				// TODO: send the action packet
			}
		}

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

	void GameView::drawMap() {
		sf::Vector2f offset(350, 100);

		// North America
		sf::ConvexShape northAmerica;
		northAmerica.setPointCount(6);
		northAmerica.setPoint(0, sf::Vector2f(50, 50));
		northAmerica.setPoint(1, sf::Vector2f(300, 50));
		northAmerica.setPoint(2, sf::Vector2f(350, 200));
		northAmerica.setPoint(3, sf::Vector2f(200, 400));
		northAmerica.setPoint(4, sf::Vector2f(100, 350));
		northAmerica.setPoint(5, sf::Vector2f(20, 150));
		northAmerica.setFillColor(sf::Color(100, 150, 250));
		northAmerica.setPosition(offset);
		window.draw(northAmerica);

		// South America
		sf::ConvexShape southAmerica;
		southAmerica.setPointCount(5);
		southAmerica.setPoint(0, sf::Vector2f(200, 420));
		southAmerica.setPoint(1, sf::Vector2f(350, 450));
		southAmerica.setPoint(2, sf::Vector2f(300, 750));
		southAmerica.setPoint(3, sf::Vector2f(200, 700));
		southAmerica.setPoint(4, sf::Vector2f(150, 500));
		southAmerica.setFillColor(sf::Color(250, 200, 100));
		southAmerica.setPosition(offset);
		window.draw(southAmerica);

		// Africa
		sf::ConvexShape africa;
		africa.setPointCount(6);
		africa.setPoint(0, sf::Vector2f(450, 300));
		africa.setPoint(1, sf::Vector2f(650, 300));
		africa.setPoint(2, sf::Vector2f(700, 500));
		africa.setPoint(3, sf::Vector2f(600, 700));
		africa.setPoint(4, sf::Vector2f(500, 650));
		africa.setPoint(5, sf::Vector2f(400, 450));
		africa.setFillColor(sf::Color(250, 100, 150));
		africa.setPosition(offset);
		window.draw(africa);

		// Asia
		sf::ConvexShape asia;
		asia.setPointCount(7);
		asia.setPoint(0, sf::Vector2f(550, 50));
		asia.setPoint(1, sf::Vector2f(900, 50));
		asia.setPoint(2, sf::Vector2f(950, 300));
		asia.setPoint(3, sf::Vector2f(800, 450));
		asia.setPoint(4, sf::Vector2f(650, 400));
		asia.setPoint(5, sf::Vector2f(550, 300));
		asia.setPoint(6, sf::Vector2f(500, 150));
		asia.setFillColor(sf::Color(150, 250, 150));
		asia.setPosition(offset);
		window.draw(asia);

		// Australia
		sf::ConvexShape australia;
		australia.setPointCount(4);
		australia.setPoint(0, sf::Vector2f(750, 550));
		australia.setPoint(1, sf::Vector2f(950, 550));
		australia.setPoint(2, sf::Vector2f(900, 750));
		australia.setPoint(3, sf::Vector2f(750, 700));
		australia.setFillColor(sf::Color(200, 100, 250));
		australia.setPosition(offset);
		window.draw(australia);
	}
>>>>>>> Stashed changes
}
