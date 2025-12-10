#include "GameView.h"

namespace TheTraitor {

	GameView::GameView(sf::RenderWindow& window) : window(window), viewData{ false, ActionType::TradePact }
	{
	}

	void GameView::render() {

	}

	const ViewData& GameView::handleInput(const InputData& inputData) {
		viewData.isActionRequested = false;

		return viewData;
	}
}
