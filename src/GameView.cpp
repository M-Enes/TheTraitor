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

		sf::VertexArray continents(sf::PrimitiveType::Triangles);

		// North America - Blue
		sf::Color northAmericaColor(100, 150, 250);
		std::vector<sf::Vector2f> northAmericaPoints = {
			sf::Vector2f(50, 50), sf::Vector2f(300, 50), sf::Vector2f(350, 200),
			sf::Vector2f(200, 400), sf::Vector2f(100, 350), sf::Vector2f(20, 150)
		};
		for (size_t i = 1; i < northAmericaPoints.size() - 1; ++i) {
			continents.append(sf::Vertex(offset + northAmericaPoints[0], northAmericaColor));
			continents.append(sf::Vertex(offset + northAmericaPoints[i], northAmericaColor));
			continents.append(sf::Vertex(offset + northAmericaPoints[i + 1], northAmericaColor));
		}

		// South America - Orange
		sf::Color southAmericaColor(250, 200, 100);
		std::vector<sf::Vector2f> southAmericaPoints = {
			sf::Vector2f(200, 420), sf::Vector2f(350, 450), sf::Vector2f(300, 750),
			sf::Vector2f(200, 700), sf::Vector2f(150, 500)
		};
		for (size_t i = 1; i < southAmericaPoints.size() - 1; ++i) {
			continents.append(sf::Vertex(offset + southAmericaPoints[0], southAmericaColor));
			continents.append(sf::Vertex(offset + southAmericaPoints[i], southAmericaColor));
			continents.append(sf::Vertex(offset + southAmericaPoints[i + 1], southAmericaColor));
		}

		// Africa - Pink
		sf::Color africaColor(250, 100, 150);
		std::vector<sf::Vector2f> africaPoints = {
			sf::Vector2f(450, 300), sf::Vector2f(650, 300), sf::Vector2f(700, 500),
			sf::Vector2f(600, 700), sf::Vector2f(500, 650), sf::Vector2f(400, 450)
		};
		for (size_t i = 1; i < africaPoints.size() - 1; ++i) {
			continents.append(sf::Vertex(offset + africaPoints[0], africaColor));
			continents.append(sf::Vertex(offset + africaPoints[i], africaColor));
			continents.append(sf::Vertex(offset + africaPoints[i + 1], africaColor));
		}

		// Asia - Light Green
		sf::Color asiaColor(150, 250, 150);
		std::vector<sf::Vector2f> asiaPoints = {
			sf::Vector2f(550, 50), sf::Vector2f(900, 50), sf::Vector2f(950, 300),
			sf::Vector2f(800, 450), sf::Vector2f(650, 400), sf::Vector2f(550, 300),
			sf::Vector2f(500, 150)
		};
		for (size_t i = 1; i < asiaPoints.size() - 1; ++i) {
			continents.append(sf::Vertex(offset + asiaPoints[0], asiaColor));
			continents.append(sf::Vertex(offset + asiaPoints[i], asiaColor));
			continents.append(sf::Vertex(offset + asiaPoints[i + 1], asiaColor));
		}

		// Australia - Purple
		sf::Color australiaColor(200, 100, 250);
		std::vector<sf::Vector2f> australiaPoints = {
			sf::Vector2f(750, 550), sf::Vector2f(950, 550),
			sf::Vector2f(900, 750), sf::Vector2f(750, 700)
		};
		for (size_t i = 1; i < australiaPoints.size() - 1; ++i) {
			continents.append(sf::Vertex(offset + australiaPoints[0], australiaColor));
			continents.append(sf::Vertex(offset + australiaPoints[i], australiaColor));
			continents.append(sf::Vertex(offset + australiaPoints[i + 1], australiaColor));
		}

		window.draw(continents);
	}
>>>>>>> Stashed changes
}
