#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "InputHandler.h"
#include "GameView.h"

namespace TheTraitor {

	class ClientApp
	{
	public:
		ClientApp();
		ClientApp(const ClientApp&) = delete;
		ClientApp& operator=(const ClientApp&) = delete;
		void run();
	private:
		sf::RenderWindow window;
		InputHandler inputHandler;
		GameView gameView;
	private:
		void update(sf::Time deltaTime);
		void render();
	};
}
