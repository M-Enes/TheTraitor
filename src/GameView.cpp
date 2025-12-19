#include "GameView.h"
#include "PolygonData.h"
#include "earcut.h"
#include "Player.h"

namespace mapbox {
	namespace util {

		template <>
		struct nth<0, sf::Vector2f> {
			inline static auto get(const sf::Vector2f& t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, sf::Vector2f> {
			inline static auto get(const sf::Vector2f& t) {
				return t.y;
			};
		};

	} // namespace util
} // namespace mapbox

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window, std::string executableFolderPath) :
		window(window),
		viewData{ false, ActionType::TradePact, GameState::NONE, "" },
		font(executableFolderPath + "/assets/fonts/CascadiaMono.ttf"),
		joinGameButton(sf::Vector2f(800, 600), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window),
		playerNameInputLabel(font),
		playerNameInputTextBox(font),
		playerNameInputTextBoxString(""),
		playerLabels({ font,font,font,font,font }),
		actionMenu({ 310, (float)window.getSize().y - 40 }),
		eventLogMenu({ (float)window.getSize().x - 370, 300 }),
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
			actionMenuButtons.push_back({ buttonString ,{
				sf::Vector2f(50, actionMenuButtonPositionY), sf::Vector2f(240, 50), sf::Vector2f(10, 10), buttonString, font, window,
				24, sf::Color::Black, sf::Color::White, 5, sf::Color(200,200,200), sf::Color::White} });
			actionMenuButtonPositionY += 100;
		}

		eventLogMenu.setPosition({ 350, (float)window.getSize().y - 320 });
		eventLogMenu.setFillColor(sf::Color::Black);
		eventLogMenu.setOutlineThickness(5);
		eventLogMenu.setOutlineColor(sf::Color::White);

		//roundLabel.setPosition({ 370, (float)window.getSize().y - 300 });
		//timerLabel.setPosition({ 370, (float)window.getSize().y - 300 });

		eventLogLabel.setPosition({ 370, (float)window.getSize().y - 250 });

		allCountries = { {
		{&americaPolygonPoints, &americaVertices},
		{&africaPolygonPoints, &africaVertices },
		{&asiaPolygonPoints,	 &asiaVertices  },
		{&australiaPolygonPoints, &australiaVertices},
		{&europePolygonPoints, &europeVertices}
		} };
		calculateCountries();

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

	void GameView::renderLobby(std::vector<TheTraitor::Player> players)
	{
		sf::Text playerCountText(font);
		playerCountText.setString("Players joined: " + std::to_string(players.size()));
		playerCountText.setCharacterSize(24);
		playerCountText.setFillColor(sf::Color::White);
		playerCountText.setPosition(sf::Vector2f(100, 100));

		int i = 0;
		for (auto& label : playerLabels) {
			if (players.size() <= i) {
				label.setString("Waiting for player...");
			}
			else {
				label.setString(players[i].getName());
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
		window.draw(actionMenu);
		for (auto& buttonPair : actionMenuButtons) {
			buttonPair.second.render();
		}

		window.draw(americaVertices);
		window.draw(africaVertices);
		window.draw(asiaVertices);
		window.draw(australiaVertices);
		window.draw(europeVertices);


		window.draw(eventLogMenu);
	/*	window.draw(roundLabel);
		window.draw(timerLabel);*/
		window.draw(eventLogLabel);
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

		for (const auto& countryPair : allCountries) {
			if (isPointInPolygon(*countryPair.first, position + sf::Vector2f{ -310.0f,0.0f })) {
				sf::Color fillColor = (inputData.isMouseClicked) ? sf::Color{ 255,0,0 } : sf::Color{ 0,200,0 };
				if ((*countryPair.second)[0].color == sf::Color{ 255,0,0 }) fillColor = sf::Color{ 0,200,0 };
				if ((*countryPair.second)[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {
					for (int i = 0; i < (*countryPair.second).getVertexCount(); i++) {
						(*countryPair.second)[i].color = fillColor;
					}

				}
			}
			else {
				if ((*countryPair.second)[0].color != sf::Color{ 255,0,0 } || inputData.isMouseClicked) {

					for (int i = 0; i < (*countryPair.second).getVertexCount(); i++) {
						(*countryPair.second)[i].color = sf::Color::Green;
					}
				}
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
	bool GameView::isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point)
	{
		bool isInside = false;

		for (int i = 0, j = 0; i < polygonPoints.size(); i++) {
			j = (i + 1) % polygonPoints.size();
			if ((point.x >= polygonPoints[i].x != point.x >= polygonPoints[j].x)
				&& point.y < polygonPoints[i].y + (polygonPoints[j].y - polygonPoints[i].y) * (point.x - polygonPoints[i].x) / (polygonPoints[j].x - polygonPoints[i].x)) {
				isInside = !isInside;
			}
		}

		return isInside;
	}
	void GameView::calculateCountries()
	{
		using N = uint16_t;

		for (const auto& countryPair : allCountries) {
			std::vector<std::vector<sf::Vector2f>> polygonWrapper;
			polygonWrapper.push_back(*countryPair.first);
			std::vector<N> indices = mapbox::earcut<N>(polygonWrapper);

			countryPair.second->setPrimitiveType(sf::PrimitiveType::Triangles);
			countryPair.second->resize(indices.size());
			int i = 0;
			for (const auto& index : indices) {
				(*countryPair.second)[i] = sf::Vertex{ (*countryPair.first)[index] + sf::Vector2f{310.0f, 0.0f}, sf::Color::Green };
				i++;
			}
		}
	}
}
