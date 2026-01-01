#include "Client/Phases/WinPhase.h"
#include <cmath>

namespace TheTraitor {

	WinPhase::WinPhase(sf::RenderWindow& window, sf::Font& font)
		: window(window), font(font), 
		viewData{ false, ActionType::TradePact, CountryType(NONE), NONE, "", 0 },
		title(font, "VICTORY!", 80),
		totalRoundsLabel(font),
		totalTimeLabel(font),
		quitGameButton(sf::Vector2f(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f + 150),
			sf::Vector2f(200, 60), 
			sf::Vector2f(45, 15), 
			"Quit Game",
			font,
			window,
			20,
			sf::Color::Black,
			sf::Color::White,
			5,
			sf::Color(200, 200, 200),
			sf::Color::White)
	{
		title.setFillColor(sf::Color::Green);
		title.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - title.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 200));
	}

	void WinPhase::render(const GameState& gameState, int localPlayerID, float elapsedTime, int roundCounter) {
		int totalTimeSeconds = static_cast<int>(elapsedTime);

		sf::RectangleShape overlay(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);

		window.draw(title);

		totalRoundsLabel.setString("Total Rounds: " + std::to_string(roundCounter));
		totalRoundsLabel.setCharacterSize(30);
		totalRoundsLabel.setFillColor(sf::Color::White);
		totalRoundsLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalRoundsLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 50));
		window.draw(totalRoundsLabel);

		totalTimeLabel.setString("Total Time: " + std::to_string(totalTimeSeconds / 60) + ":" + std::to_string(totalTimeSeconds % 60));
		totalTimeLabel.setCharacterSize(30);
		totalTimeLabel.setFillColor(sf::Color::White);
		totalTimeLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalTimeLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f + 20));
		window.draw(totalTimeLabel);

		quitGameButton.render();
	}

	const ViewData& WinPhase::handleInput(const InputData& inputData) {
		resetViewData();

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isHovered = quitGameButton.isMouseOver(position);
		quitGameButton.updateHoverEffect(isHovered);

		if (inputData.isMouseClicked && isHovered) {
			viewData.gotoState = NONE;
		}
		else {
			viewData.gotoState = WIN;
		}

		return viewData;
	}

	void WinPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

}
