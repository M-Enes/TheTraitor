#include "Client/Phases/MenuPhase.h"
#include "Client/BridgeTypes.h"

namespace TheTraitor {

	MenuPhase::MenuPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures)
		: window(window), font(font),
		viewData{ false, ActionType::TradePact, CountryType(NONE), GamePhase(NONE), "", "", "", 0, false },
		joinGameButton(sf::Vector2f(700, 800), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window,
			24, sf::Color::Black, sf::Color::White, 5, sf::Color(200, 200, 200), sf::Color::White),
		playerNameInputLabel(font),
		playerNameInputTextBox(font),
		playerNameInputTextBoxString(""),
		serverIPLabel(font),
		serverIPTextBox(font),
		serverIPTextBoxString(""),
		serverPortLabel(font),
		serverPortTextBox(font),
		serverPortTextBoxString(""),
		avatarLabel(font, "Select Avatar", 24),
		currentSelectedAvatarIndex(-1),
		titleLabel(font, "The Traitor", 60),
		howToPlayLabel(font, "", 24),
		showCursor(true)
	{
		playerNameInputLabel.setPosition(sf::Vector2f(600, 400));
		playerNameInputLabel.setString("Type your player name");

		playerNameInputTextBox.setPosition(sf::Vector2f(600, 500));
		playerNameInputTextBox.setString(playerNameInputTextBoxString);

		serverIPLabel.setPosition(sf::Vector2f(350, 600));
		serverIPLabel.setString("Server IP:");

		serverPortLabel.setPosition(sf::Vector2f(350, 700));
		serverPortLabel.setString("Server Port:");

		serverIPTextBox.setPosition(sf::Vector2f(600, 600));
		serverIPTextBox.setString(serverIPTextBoxString);

		serverPortTextBox.setPosition(sf::Vector2f(600, 700));
		serverPortTextBox.setString(serverPortTextBoxString);

		titleLabel.setPosition(sf::Vector2f(50, 50));
		titleLabel.setFillColor(sf::Color::Red);
		titleLabel.setStyle(sf::Text::Bold);

		howToPlayLabel.setString("How to play:\n\nYou will have a country and a role.\nIf you're an innocent, you need to destroy traitors country.\nIf you're the traitor, you need to destroy innocent countries.\n\nUse Tab to move between input textboxes.");
		howToPlayLabel.setPosition(sf::Vector2f(50, 150));
		howToPlayLabel.setFillColor(sf::Color::White);

		initAvatarSprites(avatarTextures);
	}

	void MenuPhase::initAvatarSprites(const std::vector<sf::Texture>& avatarTextures) {
		// Avatar Layout Configuration
		const float avatarDisplaySize = 80.0f;
		const float gap = 20.0f;
		const int cols = 5;

		// Calculate total width to right-align
		float totalGridWidth = cols * avatarDisplaySize + (cols - 1) * gap;

		float startX = window.getSize().x - totalGridWidth - 150.0f;
		float startY = 350.0f;

		avatarSprites.reserve(avatarTextures.size());
		for (size_t i = 0; i < avatarTextures.size(); ++i) {
			sf::Sprite sprite(avatarTextures[i]);

			// Scale to fixed size
			sf::Vector2u texSize = avatarTextures[i].getSize();
			if (texSize.x > 0 && texSize.y > 0) {
				sprite.setScale({
					avatarDisplaySize / static_cast<float>(texSize.x),
					avatarDisplaySize / static_cast<float>(texSize.y)
					});
			}

			int col = i % cols;
			int row = i / cols;

			float x = startX + col * (avatarDisplaySize + gap);
			float y = startY + row * (avatarDisplaySize + gap);

			sprite.setPosition({ x, y });
			avatarSprites.push_back(sprite);
		}

		avatarLabel.setPosition({ startX, startY - 40.f });
	}

	void MenuPhase::render(const GameState& gameState, int localPlayerID, float elapsedTime, int roundCounter) {
		if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
			showCursor = !showCursor;
			blinkClock.restart();
		}
		if (tabIndex == 0) {
			playerNameInputTextBox.setString(playerNameInputTextBoxString + (showCursor ? "|" : ""));
		}
		else if (tabIndex == 1) {
			serverIPTextBox.setString(serverIPTextBoxString + (showCursor ? "|" : ""));
		}
		else {
			serverPortTextBox.setString(serverPortTextBoxString + (showCursor ? "|" : ""));
		}

		window.draw(titleLabel);
		window.draw(howToPlayLabel);
		window.draw(playerNameInputLabel);
		window.draw(playerNameInputTextBox);
		window.draw(serverIPLabel);
		window.draw(serverIPTextBox);
		window.draw(serverPortLabel);
		window.draw(serverPortTextBox);

		// Draw Avatar Background (Table feel)
		if (!avatarSprites.empty()) {
			sf::Vector2f firstPos = avatarSprites.front().getPosition();
			sf::Vector2f lastPos = avatarSprites.back().getPosition();
			sf::Vector2f size = {
				avatarSprites.front().getGlobalBounds().size.x,
				avatarSprites.front().getGlobalBounds().size.y
			};

			float padding = 10.0f;
			sf::RectangleShape bgRect;
			bgRect.setPosition({ firstPos.x - padding, firstPos.y - padding });

			float width = (lastPos.x + size.x) - firstPos.x + 2 * padding;
			float height = (lastPos.y + size.y) - firstPos.y + 2 * padding;

			bgRect.setSize({ width, height });
			bgRect.setFillColor(sf::Color(50, 50, 50, 150)); // Semi-transparent dark gray
			bgRect.setOutlineColor(sf::Color::White);
			bgRect.setOutlineThickness(2.0f);
			window.draw(bgRect);
		}

		window.draw(avatarLabel);

		for (size_t i = 0; i < avatarSprites.size(); ++i) {
			window.draw(avatarSprites[i]);

			if (currentSelectedAvatarIndex == static_cast<int>(i)) {
				sf::RectangleShape selectionRect;
				selectionRect.setSize({
					avatarSprites[i].getGlobalBounds().size.x + 6,
					avatarSprites[i].getGlobalBounds().size.y + 6
					});
				selectionRect.setPosition({
					avatarSprites[i].getPosition().x - 3,
					avatarSprites[i].getPosition().y - 3
					});
				selectionRect.setFillColor(sf::Color::Transparent);
				selectionRect.setOutlineColor(sf::Color::Yellow);
				selectionRect.setOutlineThickness(3);
				window.draw(selectionRect);
			}
		}

		joinGameButton.render();
	}

	const ViewData& MenuPhase::handleInput(const InputData& inputData) {
		resetViewData();

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isJoinGameButtonHovered = joinGameButton.isMouseOver(position);
		joinGameButton.updateHoverEffect(isJoinGameButtonHovered);

		if (inputData.isMouseClicked) {
			if (isJoinGameButtonHovered) {
				viewData.enteredPlayerName = playerNameInputTextBoxString;
				viewData.enteredServerIP = serverIPTextBoxString;
				viewData.enteredServerPort = serverPortTextBoxString;
				viewData.gotoState = LOBBY;
			}

			for (size_t i = 0; i < avatarSprites.size(); ++i) {
				if (avatarSprites[i].getGlobalBounds().contains(position)) {
					currentSelectedAvatarIndex = static_cast<int>(i);
					viewData.avatarID = currentSelectedAvatarIndex;
				}
			}
		}

		if (inputData.isKeyEntered) {
			char key = inputData.keyEntered;

			if (tabIndex == 1) { // Server IP
				if (key == 8) { // Backspace
					if (!serverIPTextBoxString.empty()) {
						serverIPTextBoxString.pop_back();
					}
				}
				else if (key == 9) { // Tab
					tabIndex = (tabIndex + 1) % 3;
				}
				else {
					serverIPTextBoxString += key;
				}
				serverIPTextBox.setString(serverIPTextBoxString);
			}
			else if (tabIndex == 2) { // Server Port
				if (key == 8) { // Backspace
					if (!serverPortTextBoxString.empty()) {
						serverPortTextBoxString.pop_back();
					}
				}
				else if (key == 9) { // Tab
					tabIndex = (tabIndex + 1) % 3;
				}
				else {
					serverPortTextBoxString += key;
				}
				serverPortTextBox.setString(serverPortTextBoxString);
			}
			else {
				if (key == 8) { // Backspace
					if (!playerNameInputTextBoxString.empty()) {
						playerNameInputTextBoxString.pop_back();
					}
				}
				else if (key == 13) { // Enter
					// Optional: Trigger join if Name is valid
				}
				else if (key == 9) { // Tab
					tabIndex = (tabIndex + 1) % 3;
				}
				else {
					if (playerNameInputTextBoxString.size() < playerNameCharLimit) {
						playerNameInputTextBoxString += key;
					}
				}
				playerNameInputTextBox.setString(playerNameInputTextBoxString);
			}
		}

		return viewData;
	}

	void MenuPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}
}
