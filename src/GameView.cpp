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

<<<<<<< Updated upstream
=======
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
			actionMenuButtons.push_back({ buttonString ,{
				sf::Vector2f(50, actionMenuButtonPositionY), sf::Vector2f(240, 50), sf::Vector2f(10, 10), buttonString, font, window,
				24, sf::Color::Black, sf::Color::White, 5, sf::Color(200,200,200), sf::Color::White} });
			actionMenuButtonPositionY += 100;
		}

		eventLogMenu.setPosition({ (float)window.getSize().x - 560,20 });
		eventLogMenu.setFillColor({ 30, 30, 30 });

		roundLabel.setPosition({ (float)window.getSize().x - 500, 20 });
		timerLabel.setPosition({ (float)window.getSize().x - 200, 20 });

		eventLogLabel.setPosition({ (float)window.getSize().x - 540, 80 });

		using N = uint16_t;
		std::vector<std::vector<sf::Vector2f>> americaPolygonPointsWrapper;
		americaPolygonPointsWrapper.push_back(americaPolygonPoints);
		std::vector<N> indices = mapbox::earcut<N>(americaPolygonPointsWrapper);

		americaVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
		americaVertices.resize(indices.size());
		int i = 0;
		for (const auto& index : indices) {
			americaVertices[i] = sf::Vertex{ americaPolygonPoints[index] + sf::Vector2f{350.0f, 0.0f}, sf::Color::Green };
			i++;
		}

		std::vector<std::vector<sf::Vector2f>> africaPolygonPointsWrapper;
		africaPolygonPointsWrapper.push_back(africaPolygonPoints);
		std::vector<N> africaIndices = mapbox::earcut<N>(africaPolygonPointsWrapper);

		africaVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
		africaVertices.resize(africaIndices.size());
		i = 0;
		for (const auto& index : africaIndices) {
			africaVertices[i] = sf::Vertex{ africaPolygonPoints[index] + sf::Vector2f{350.0f, 0.0f}, sf::Color::Yellow };
			i++;
		}

		std::vector<std::vector<sf::Vector2f>> asiaPolygonPointsWrapper;
		asiaPolygonPointsWrapper.push_back(asiaPolygonPoints);
		std::vector<N> asiaIndices = mapbox::earcut<N>(asiaPolygonPointsWrapper);

		asiaVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
		asiaVertices.resize(asiaIndices.size());
		i = 0;
		for (const auto& index : asiaIndices) {
			asiaVertices[i] = sf::Vertex{ asiaPolygonPoints[index] + sf::Vector2f{350.0f, 0.0f}, sf::Color::Blue };
			i++;
		}

		std::vector<std::vector<sf::Vector2f>> australiaPolygonPointsWrapper;
		australiaPolygonPointsWrapper.push_back(australiaPolygonPoints);
		std::vector<N> australiaIndices = mapbox::earcut<N>(australiaPolygonPointsWrapper);

		australiaVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
		australiaVertices.resize(australiaIndices.size());
		i = 0;
		for (const auto& index : australiaIndices) {
			australiaVertices[i] = sf::Vertex{ australiaPolygonPoints[index] + sf::Vector2f{350.0f, 0.0f}, sf::Color::Red };
			i++;
		}

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
		drawMap();
=======
		window.draw(americaVertices);
		window.draw(africaVertices);
		window.draw(asiaVertices);
		window.draw(australiaVertices);

>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
=======
		//America
		if (isPointInPolygon(americaPolygonPoints, position + sf::Vector2f{ -350.0f,0.0f })) {
			sf::Color fillColor = (inputData.isMouseClicked) ? sf::Color{ 255,0,0 } : sf::Color{ 0,200,0 };
			if (americaVertices[0].color == sf::Color{ 255,0,0 }) fillColor = sf::Color{ 0,200,0 };
			if (americaVertices[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {
				for (int i = 0; i < americaVertices.getVertexCount(); i++) {
					americaVertices[i].color = fillColor;
				}

			}
		}
		else {
			if (americaVertices[0].color != sf::Color{ 255,0,0 }) {

				for (int i = 0; i < americaVertices.getVertexCount(); i++) {
					americaVertices[i].color = sf::Color::Green;
				}
			}
		}

		//Africa
		if (isPointInPolygon(africaPolygonPoints, position + sf::Vector2f{ -350.0f,0.0f })) {
			sf::Color fillColor = (inputData.isMouseClicked) ? sf::Color{ 255,0,0 } : sf::Color{ 0,200,0 };
			if (africaVertices[0].color == sf::Color{ 255,0,0 }) fillColor = sf::Color{ 0,200,0 };
			if (africaVertices[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {
				for (int i = 0; i < africaVertices.getVertexCount(); i++) {
					africaVertices[i].color = fillColor;
				}

			}
		}
		else {
			if (africaVertices[0].color != sf::Color{ 255,0,0 }) {

				for (int i = 0; i < africaVertices.getVertexCount(); i++) {
					africaVertices[i].color = sf::Color::Yellow;
				}
			}
		}

		//Asia
		if (isPointInPolygon(asiaPolygonPoints, position + sf::Vector2f{ -350.0f,0.0f })) {
			sf::Color fillColor = (inputData.isMouseClicked) ? sf::Color{ 255,0,0 } : sf::Color{ 0,200,0 };
			if (asiaVertices[0].color == sf::Color{ 255,0,0 }) fillColor = sf::Color{ 0,200,0 };
			if (asiaVertices[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {
				for (int i = 0; i < asiaVertices.getVertexCount(); i++) {
					asiaVertices[i].color = fillColor;
				}

			}
		}
		else {
			if (asiaVertices[0].color != sf::Color{ 255,0,0 }) {

				for (int i = 0; i < asiaVertices.getVertexCount(); i++) {
					asiaVertices[i].color = sf::Color::Blue;
				}
			}
		}

		//Australia
		if (isPointInPolygon(australiaPolygonPoints, position + sf::Vector2f{ -350.0f,0.0f })) {
			sf::Color fillColor = (inputData.isMouseClicked) ? sf::Color{ 255,0,0 } : sf::Color{ 0,200,0 };
			if (australiaVertices[0].color == sf::Color{ 255,0,0 }) fillColor = sf::Color{ 0,200,0 };
			if (australiaVertices[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {
				for (int i = 0; i < australiaVertices.getVertexCount(); i++) {
					australiaVertices[i].color = fillColor;
				}

			}
		}
		else {
			if (australiaVertices[0].color != sf::Color{ 255,0,0 }) {

				for (int i = 0; i < australiaVertices.getVertexCount(); i++) {
					australiaVertices[i].color = sf::Color::Red;
				}
			}
		}



>>>>>>> Stashed changes
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
