#include "GameView.h"

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window) : 
		window(window),
		viewData{ false, ActionType::TradePact, GameState::NONE },
		font("assets/fonts/CascadiaMono.ttf"),
		joinGameButton(sf::Vector2f(800, 600), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window)
	{
	}

	void GameView::renderMenu()
	{
		joinGameButton.render();
	}

	void GameView::renderLobby()
	{
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

		return viewData;
	}
}
