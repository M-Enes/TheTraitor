#include "ClientApp.h"

namespace TheTraitor {

	void ClientApp::run()
	{
		sf::Clock clock;

		while (window.isOpen()) {
			sf::Time deltaTime = clock.restart();

			update(deltaTime);
			render();
		}
	}

	void ClientApp::update(sf::Time deltaTime)
	{
		inputHandler.handleEvents();
		const InputData& inputData = inputHandler.getInputData();

		const ViewData& viewData = gameView.handleInput(inputData);

		if (viewData.isActionRequested) {
			// TODO: send action packet
		}
	}

	void ClientApp::render()
	{
		window.clear(sf::Color(0, 0, 0, 255));
		gameView.render();
		window.display();
	}

	ClientApp::ClientApp() : window(sf::VideoMode::getDesktopMode(), "The Traitor", sf::Style::None), inputHandler(window), gameView(window)
	{
		window.setFramerateLimit(60);
	}

}