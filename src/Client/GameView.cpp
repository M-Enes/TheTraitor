#include "GameView.h"
#include "PolygonData.h"
#include "vendor/earcut.hpp"
#include "Common/Player.h"
#include "Common/GameState.h"

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
		viewData{ false, ActionType::TradePact, 0, NONE, "", 0 },
		font(executableFolderPath + "/assets/fonts/CascadiaMono.ttf"),
		joinGameButton(sf::Vector2f(800, 600), sf::Vector2f(150, 50), sf::Vector2f(10, 10), "Join Game", font, window,
			24, sf::Color::Black, sf::Color::White, 5, sf::Color(200, 200, 200), sf::Color::White),
		playerNameInputLabel(font),
		playerNameInputTextBox(font),
		playerNameInputTextBoxString(""),
		playerLabels({ font,font,font,font,font }),
		actionMenu({ 310, (float)window.getSize().y - 40 }),
		eventLogMenu({ (float)window.getSize().x - 870, 300 }),
		eventLogString("MuhammedEnesKrc made Trade Pact with MuhammedEnesKrc\n"
			"MuhammedEnesKrc applied Trade Embargo to MuhammedEnesKrc"),
		eventLogMenuLabel(font, "Event Log"),
		eventLogLabel(font, eventLogString, 20),
		infoMenu({ 480, (float)window.getSize().y - 40 }),
		topBar({ 1050, 120 }),
		roundLabel(font, "Round 1"),
		phaseLabel(font, "Action Phase"),
		timerLabel(font, "01:02"),
		playerInfo({ { {font, font, font, font},
			{font, font, font, font},
			{font, font, font, font},
			{font, font, font, font},
			{font, font, font, font} } }),
		economyIconTexture(executableFolderPath + "/assets/icons/icons8-cash-64.png"),
		healthIconTexture(executableFolderPath + "/assets/icons/icons8-medical-kit-64.png"),
		educationIconTexture(executableFolderPath + "/assets/icons/icons8-book-64.png"),
		economyIconSprite(economyIconTexture),
		healthIconSprite(healthIconTexture),
		educationIconSprite(educationIconTexture),
		countryNormalColor(sf::Color::Green),
		countryHoverColor(sf::Color{ 0,200,0 }),
		countrySelectedColor(sf::Color::Red),
		countriesOffset(sf::Vector2f{ 310.0f, -50.0f }),
		avatarLabel(font, "Select Avatar", 24),
		currentSelectedAvatarIndex(-1),
		gameoverTitle(font, "GAME OVER", 80),
		winTitle(font, "VICTORY!", 80),
		totalRoundsLabel(font),
		totalTimeLabel(font),
		quitGameButton(sf::Vector2f(window.getSize().x / 2.0f - 100, window.getSize().y / 2.0f + 150), //position
			sf::Vector2f(200, 60), // size of the button
			sf::Vector2f(45, 15), // position offset for text inside the button
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

		std::array<ActionType, 9> actionTypes{
			ActionType::TradePact,
			ActionType::TradeEmbargo,
			ActionType::JointResearch,
			ActionType::SpreadMisinfo,
			ActionType::HealthAid,
			ActionType::PoisonResources,
			ActionType::SabotageFactory,
			ActionType::DestroySchool,
			ActionType::SpreadPlague
		};

		float actionMenuButtonPositionY = 100;

		actionMenuButtons.reserve(actionMenuButtonStrings.size());
		int buttonIndex = 0;
		for (const auto& buttonString : actionMenuButtonStrings) {
			actionMenuButtons.push_back({ buttonString ,
				{
				sf::Vector2f(50, actionMenuButtonPositionY), sf::Vector2f(240, 50), sf::Vector2f(10, 10), buttonString, font, window,
				24, sf::Color::Black, sf::Color::White, 5, sf::Color(200,200,200), sf::Color::White
				},
				actionTypes[buttonIndex]
				});
			actionMenuButtonPositionY += 100;
			buttonIndex++;
		}

		eventLogMenu.setPosition({ 350, (float)window.getSize().y - 320 });
		eventLogMenu.setFillColor(sf::Color::Black);
		eventLogMenu.setOutlineThickness(5);
		eventLogMenu.setOutlineColor(sf::Color::White);


		eventLogMenuLabel.setPosition({ 370, (float)window.getSize().y - 300 });
		eventLogLabel.setPosition({ 370, (float)window.getSize().y - 250 });


		infoMenu.setPosition({ (float)window.getSize().x - 500, 20 });
		infoMenu.setFillColor(sf::Color::Black);
		infoMenu.setOutlineThickness(5);
		infoMenu.setOutlineColor(sf::Color::White);

		topBar.setPosition({ 350, 20 });
		topBar.setFillColor(sf::Color::Black);
		topBar.setOutlineThickness(5);
		topBar.setOutlineColor(sf::Color::White);

		roundLabel.setPosition({ 370, 40 });
		phaseLabel.setPosition({ 750, 40 });
		timerLabel.setPosition({ 1280, 40 });

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

		sf::Vector2f labelPosition(180, 200);
		for (auto& label : playerLabels) {
			label.setPosition(labelPosition);
			labelPosition += {0, 100};
		}

		playerNameInputLabel.setPosition(sf::Vector2f(600, 500));
		playerNameInputLabel.setString("Player name");

		playerNameInputTextBox.setPosition(sf::Vector2f(600, 300));
		playerNameInputTextBox.setString(playerNameInputTextBoxString);

		// Avatar Loading
		avatarTextures.reserve(10);
		avatarSprites.reserve(10);

		for (int i = 1; i <= 10; ++i) {
			sf::Texture texture;
			if (texture.loadFromFile(
				executableFolderPath + "/assets/avatars/pixel" + std::to_string(i) + ".png")) {
				avatarTextures.push_back(std::move(texture));
			}
		}

		// Avatar Layout Configuration
		const float avatarDisplaySize = 80.0f; // Increased size (was 64.0f)
		const float gap = 20.0f; // Increased gap (was 15.0f)
		const int cols = 5;

		// Calculate total width to right-align
		float totalGridWidth = cols * avatarDisplaySize + (cols - 1) * gap;

		float startX = window.getSize().x - totalGridWidth - 150.0f; // Moved left (was 100.0f)
		float startY = 350.0f; // Moved down (was 300.0f)

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

	void GameView::renderMenu()
	{
		window.draw(playerNameInputLabel);
		window.draw(playerNameInputTextBox);

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

	void GameView::renderLobby(const GameState& gameState)
	{
		sf::Text playerCountText(font);
		playerCountText.setString("Players joined: " + std::to_string(gameState.players.size()));
		playerCountText.setCharacterSize(24);
		playerCountText.setFillColor(sf::Color::White);
		playerCountText.setPosition(sf::Vector2f(100, 100));

		long unsigned int i = 0;
		for (auto& label : playerLabels) {
			if (gameState.players.size() <= i) {
				label.setString("Waiting for player...");
			}
			else {
				label.setString(gameState.players[i].getName());

				// Draw Avatar
				int avatarID = gameState.players[i].getAvatarID();
				if (avatarID >= 0 && avatarID < static_cast<int>(avatarTextures.size())) {
					sf::Sprite avatarSprite(avatarTextures[avatarID]);
					float size = 50.0f;
					sf::Vector2u texSize = avatarTextures[avatarID].getSize();
					if (texSize.x > 0 && texSize.y > 0) {
						avatarSprite.setScale({ size / texSize.x, size / texSize.y });
					}

					// Position to the left of the name (assuming name is at x=100)
					sf::Vector2f pos = label.getPosition();
					avatarSprite.setPosition({ 100.0f, pos.y - 10.0f });
					window.draw(avatarSprite);
				}
			}
			window.draw(label);
			i++;
		}

		window.draw(playerCountText);
	}

	void GameView::renderDiscussionPhase(const GameState& gameState)
	{
	}

	void GameView::renderActionPhase(const GameState& gameState, int elapsedTimeSeconds, int roundCounter)
	{
		window.draw(actionMenu);
		for (auto& buttonPair : actionMenuButtons) {
			std::get<1>(buttonPair).render();
		}

		for (const auto& [points, vertices] : allCountries) {
			window.draw(*vertices);
		}

		window.draw(eventLogMenu);
		window.draw(eventLogMenuLabel);
		window.draw(eventLogLabel);
		window.draw(infoMenu);

		int posY = 50;
		int index = 0;

		for (const auto& player : gameState.players) {
			auto& [name, economy, health, education] = playerInfo[0];
			name.setString(player.getName());
			name.setCharacterSize(30);
			name.setPosition({ (float)window.getSize().x - 480, (float)posY });
			economyIconSprite.setPosition({ (float)window.getSize().x - 480, (float)posY + 80 });
			economy.setString(std::to_string(player.getCountry()->getEconomy()));
			economy.setCharacterSize(25);
			economy.setPosition({ (float)window.getSize().x - 400, (float)posY + 110 });
			healthIconSprite.setPosition({ (float)window.getSize().x - 360, (float)posY + 80 });
			health.setString(std::to_string(player.getCountry()->getHealth()));
			health.setCharacterSize(25);
			health.setPosition({ (float)window.getSize().x - 280, (float)posY + 110 });
			educationIconSprite.setPosition({ (float)window.getSize().x - 240, (float)posY + 90 });
			education.setString(std::to_string(player.getCountry()->getEducation()));
			education.setCharacterSize(25);
			education.setPosition({ (float)window.getSize().x - 160, (float)posY + 110 });

			// Draw Avatar in Action Phase
			int avatarID = player.getAvatarID();
			if (avatarID >= 0 && avatarID < static_cast<int>(avatarTextures.size())) {
				sf::Sprite avatarSprite(avatarTextures[avatarID]);
				float size = 64.0f; // Size for action phase
				sf::Vector2u texSize = avatarTextures[avatarID].getSize();
				if (texSize.x > 0 && texSize.y > 0) {
					avatarSprite.setScale({ size / texSize.x, size / texSize.y });
				}
				// Position to the right of the name (Fixed column)
				//decrease f to move right, increase y with f to move up (posY + 10.0f)
				avatarSprite.setPosition({ (float)window.getSize().x - 120.0f, (float)posY + 80.0f });
				window.draw(avatarSprite);
			}

			posY += 200;
			index++;
			window.draw(name);
			window.draw(economy);
			window.draw(health);
			window.draw(education);
			window.draw(economyIconSprite);
			window.draw(healthIconSprite);
			window.draw(educationIconSprite);
		}

		for (const auto& [points, vertices] : allCountries) {
			// TODO: add player info hovering/selection synced with country hovering/selection
			// also add action effects near the affected stats (e.g. green +10 for positive red -10 for negative)
		}

		window.draw(topBar);
		roundLabel.setString("Round " + std::to_string(roundCounter));
		window.draw(roundLabel);
		window.draw(phaseLabel);
		int remainingSeconds = 90 - elapsedTimeSeconds;
		timerLabel.setString(std::to_string(remainingSeconds / 60) + ":" + std::to_string(remainingSeconds % 60));
		window.draw(timerLabel);
	}

	void GameView::renderResolutionPhase(const GameState& gameState)
	{
		// 1. Clear the background or add a semi-transparent layer (optional)
		sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);

		// 2. Title
		sf::Text title(font, "Resolution Phase - Action Log", 40);
		title.setFillColor(sf::Color::Yellow);
		title.setPosition(sf::Vector2f(window.getSize().x / 2.0f - title.getGlobalBounds().size.x / 2.0f, 50));
		window.draw(title);

		// 3. Manual ActionPacket List (As requested)
		std::vector<ActionPacket> actions = {
			{ ActionType::TradePact, 0, 1 },
			{ ActionType::SabotageFactory, 1, 2 },
			{ ActionType::HealthAid, 2, 0 },
			{ ActionType::SpreadMisinfo, 0, 2 },
			{ ActionType::TradeEmbargo, 1, 0 }
		};

		// 4. Helper lambda to convert ActionTypes to String
		auto actionToString = [](ActionType type) -> std::string {
			switch (type) {
			case ActionType::TradePact: return "Trade Pact";
			case ActionType::TradeEmbargo: return "Trade Embargo";
			case ActionType::JointResearch: return "Joint Research";
			case ActionType::SpreadMisinfo: return "Spread Misinfo";
			case ActionType::HealthAid: return "Health Aid";
			case ActionType::PoisonResources: return "Poison Resources";
			case ActionType::SabotageFactory: return "Sabotage Factory";
			case ActionType::DestroySchool: return "Destroy School";
			case ActionType::SpreadPlague: return "Spread Plague";
			default: return "Unknown Action";
			}
		};

		// 5. Render the list to the screen
		float startY = 150.0f;
		float startX = 200.0f;
		int index = 1;

		for (const auto& action : actions) {
			std::string sourceName = "Unknown";
			std::string targetName = "Unknown";

			// Attempt to fetch player names from GameState (Safe access)
			if (action.sourceID >= 0 && action.sourceID < (int)gameState.players.size()) {
				sourceName = gameState.players[action.sourceID].getName();
			}
			if (action.targetID >= 0 && action.targetID < (int)gameState.players.size()) {
				targetName = gameState.players[action.targetID].getName();
			}

			// Format: [1] Ali --( Sabotage Factory )--> Veli
			std::string logText = "[" + std::to_string(index) + "] " + 
				sourceName + " --( " + actionToString(action.actionType) + " )--> " + targetName;

			sf::Text logEntry(font, logText, 24);
			logEntry.setFillColor(sf::Color::White);
			logEntry.setPosition(sf::Vector2f(startX, startY));
			
			// Visual effect: Source player's color (Optional, white for now)
			
			window.draw(logEntry);

			// Avatar drawing (Optional: We can place the source player's avatar at the start of the line)
			if (action.sourceID >= 0 && action.sourceID < (int)gameState.players.size()) {
				int avatarID = gameState.players[action.sourceID].getAvatarID();
				if (avatarID >= 0 && avatarID < (int)avatarTextures.size()) {
					sf::Sprite avatar(avatarTextures[avatarID]);
					avatar.setScale({ 32.0f / avatar.getLocalBounds().size.x, 32.0f / avatar.getLocalBounds().size.y });
					avatar.setPosition({ startX - 40.0f, startY });
					window.draw(avatar);
				}
			}

			startY += 50.0f; // Line spacing
			index++;
		}
	}

	void GameView::renderGameover(const GameState& gameState, int totalTimeSeconds, int roundCounter)
	{
		// Background overlay
		sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);

		// Game Over title (red)
		gameoverTitle.setFillColor(sf::Color::Red);
		gameoverTitle.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - gameoverTitle.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 200));
		window.draw(gameoverTitle);

		// Total rounds
		totalRoundsLabel.setString("Total Rounds: " + std::to_string(roundCounter)); // TODO: Get actual value from game state
		totalRoundsLabel.setCharacterSize(30);
		totalRoundsLabel.setFillColor(sf::Color::White);
		totalRoundsLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalRoundsLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 50));
		window.draw(totalRoundsLabel);

		// Total time
		totalTimeLabel.setString("Total Time: " + std::to_string(totalTimeSeconds / 60) + ":" + std::to_string(totalTimeSeconds % 60)); // TODO: Get actual value from game state
		totalTimeLabel.setCharacterSize(30);
		totalTimeLabel.setFillColor(sf::Color::White);
		totalTimeLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalTimeLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f + 20));
		window.draw(totalTimeLabel);

		// Return to menu button
		quitGameButton.render();
	}

	void GameView::renderWin(const GameState& gameState, int totalTimeSeconds, int roundCounter)
	{
		// Background overlay
		sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
		overlay.setFillColor(sf::Color(0, 0, 0, 200));
		window.draw(overlay);

		// Victory title (green)
		winTitle.setFillColor(sf::Color::Green);
		winTitle.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - winTitle.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 200));
		window.draw(winTitle);

		// Total rounds
		totalRoundsLabel.setString("Total Rounds: " + std::to_string(roundCounter)); // TODO: Get actual value from game state
		totalRoundsLabel.setCharacterSize(30);
		totalRoundsLabel.setFillColor(sf::Color::White);
		totalRoundsLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalRoundsLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f - 50));
		window.draw(totalRoundsLabel);

		// Total time
		totalTimeLabel.setString("Total Time: " + std::to_string(totalTimeSeconds / 60) + ":" + std::to_string(totalTimeSeconds % 60)); // TODO: Get actual value from game state
		totalTimeLabel.setCharacterSize(30);
		totalTimeLabel.setFillColor(sf::Color::White);
		totalTimeLabel.setPosition(sf::Vector2f(
			window.getSize().x / 2.0f - totalTimeLabel.getGlobalBounds().size.x / 2.0f,
			window.getSize().y / 2.0f + 20));
		window.draw(totalTimeLabel);		// Return to menu button
		quitGameButton.render();
	}

	const ViewData& GameView::handleMenuInput(const InputData& inputData) {
		resetViewData();

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isHovered = joinGameButton.isMouseOver(position);
		joinGameButton.updateHoverEffect(isHovered);

		if (inputData.isMouseClicked) {

			if (isHovered) {
				viewData.enteredPlayerName = playerNameInputTextBoxString;
				viewData.gotoState = LOBBY;
			}

			for (size_t i = 0; i < avatarSprites.size(); ++i) {
				if (avatarSprites[i].getGlobalBounds().contains(position)) {
					currentSelectedAvatarIndex = i;
					viewData.avatarID = currentSelectedAvatarIndex;
				}
			}
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
		for (auto& [name, button, actionType] : actionMenuButtons) {
			isHovered = false;
			isHovered = button.isMouseOver(position);

			button.updateHoverEffect(isHovered);

			if (inputData.isMouseClicked && isHovered) {
				// TODO: send the action packet
				viewData.isActionRequested = true;
				viewData.actionType = actionType;
				viewData.actionTargetID = 1;// TODO: fill this with targetID
			}
		}

		for (const auto& countryPair : allCountries) {
			if (isPointInPolygon(*countryPair.first, position - countriesOffset)) {
				sf::Color fillColor = (inputData.isMouseClicked) ? countrySelectedColor : countryHoverColor;
				if ((*countryPair.second)[0].color == countrySelectedColor) fillColor = countryHoverColor;
				if ((*countryPair.second)[0].color != countrySelectedColor || inputData.isMouseClicked) {
					for (long unsigned int i = 0; i < (*countryPair.second).getVertexCount(); i++) {
						(*countryPair.second)[i].color = fillColor;
					}

				}
			}
			else {
				if ((*countryPair.second)[0].color != countrySelectedColor || inputData.isMouseClicked) {

					for (long unsigned int i = 0; i < (*countryPair.second).getVertexCount(); i++) {
						(*countryPair.second)[i].color = countryNormalColor;
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

	const ViewData& GameView::handleGameoverInput(const InputData& inputData)
	{
		resetViewData();

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isHovered = quitGameButton.isMouseOver(position);
		quitGameButton.updateHoverEffect(isHovered);

		if (inputData.isMouseClicked && isHovered) {
			viewData.gotoState = NONE;
		}
		else {
			viewData.gotoState = GAMEOVER;
		}

		return viewData;
	}

	const ViewData& GameView::handleWinInput(const InputData& inputData)
	{
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

	void GameView::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

	const ViewData& GameView::getViewData() {
		return viewData;
	}



	bool GameView::isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point)
	{
		bool isInside = false;

		for (long unsigned int i = 0, j = 0; i < polygonPoints.size(); i++) {
			j = (i + 1) % polygonPoints.size();
			if (((point.x >= polygonPoints[i].x) != (point.x >= polygonPoints[j].x))
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
				(*countryPair.second)[i] = sf::Vertex{ (*countryPair.first)[index] + countriesOffset, sf::Color::Green };
				i++;
			}
		}
	}
}
