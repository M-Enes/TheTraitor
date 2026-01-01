#include "Client/Phases/ActionPhase.h"
#include "Client/PolygonData.h"
#include "vendor/earcut.hpp"
#include "Common/Role.h"

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

	ActionPhase::ActionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures, std::string executableFolderPath)
		: window(window), font(font), avatarTextures(avatarTextures),
		viewData{ false, ActionType::TradePact, CountryType(NONE), NONE, "", 0},
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
		playerInfo({ {font, font, font, font}}),
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
		isTraitor(false)
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
	}

	void ActionPhase::calculateCountries()
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

	bool ActionPhase::isPointInPolygon(const std::vector<sf::Vector2f>& polygonPoints, sf::Vector2f point)
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

	void ActionPhase::render(const GameState& gameState, int localPlayerID, float elapsedTimeSeconds, int roundCounter)
	{
		// Identify if the local player is a traitor
		for (const auto& player : gameState.players) {
			if (player.getPlayerID() == localPlayerID) {
				if (player.getRole()->getName() == "Traitor") {
					isTraitor = true;
				} else {
					isTraitor = false;
				}
				break;
			}
		}

		window.draw(actionMenu);
		for (auto& buttonPair : actionMenuButtons) {
			if (!isTraitor && (std::get<2>(buttonPair) == ActionType::SabotageFactory ||
				 std::get<2>(buttonPair) == ActionType::DestroySchool ||
				 std::get<2>(buttonPair) == ActionType::SpreadPlague)) {
					std::get<1>(buttonPair).setShapeOutlineColor(sf::Color(255,255,255,128));
					std::get<1>(buttonPair).setLabelFillColor(sf::Color(255,255,255,128));
				}
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
			auto& [name, economy, health, education] = playerInfo;

			std::string displayName = player.getName();
			if (player.getPlayerID() == localPlayerID) {
				displayName += " (You)";
			}

			// Highlight player info if country is hovered or selected
			sf::RectangleShape highlightRect;
			highlightRect.setPosition({ (float)window.getSize().x - 500, (float)posY - 10 });
			highlightRect.setSize({ 480, 190 });
			highlightRect.setFillColor(sf::Color::Transparent);

			CountryType type = player.getCountry()->getType();
			int typeIndex = static_cast<int>(type);
			if (type != CountryType::NONE && typeIndex >= 0 && typeIndex < 5) {
				sf::Color currentColor = (*allCountries[typeIndex].second)[0].color;
				if (currentColor == countrySelectedColor) {
					highlightRect.setFillColor(sf::Color(150, 0, 50, 128)); 
				} else if (currentColor == countryHoverColor) {
					highlightRect.setFillColor(sf::Color(0, 150, 50, 128));
				}
			}
			window.draw(highlightRect);

			name.setString(displayName);
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

		window.draw(topBar);
		roundLabel.setString("Round " + std::to_string(roundCounter));
		window.draw(roundLabel);
		window.draw(phaseLabel);
		int remainingSeconds = 90 - (int)elapsedTimeSeconds;
		timerLabel.setString(std::to_string(remainingSeconds / 60) + ":" + std::to_string(remainingSeconds % 60));
		window.draw(timerLabel);
	}

	const ViewData& ActionPhase::handleInput(const InputData& inputData) {
		resetViewData();

		sf::Vector2f position = window.mapPixelToCoords(inputData.mousePosition);

		bool isHovered;
		for (auto& [name, button, actionType] : actionMenuButtons) {
			// Check if it is a secret action
			if (actionType == ActionType::SabotageFactory ||
				actionType == ActionType::DestroySchool ||
				actionType == ActionType::SpreadPlague) {

				if (!isTraitor) continue;
			}
			isHovered = false;
			isHovered = button.isMouseOver(position);

			button.updateHoverEffect(isHovered);

			if (inputData.isMouseClicked && isHovered) {

				viewData.isActionRequested = true;
				viewData.actionType = actionType;
				// set targetID based on the country that is color is selected color
				viewData.actionTargetCountryType = CountryType::NONE;
				int typeIndex = 0;
				for (const auto& countryPair : allCountries) {
					if ((*countryPair.second)[0].color == countrySelectedColor) {
						break;
					}
					typeIndex++;
				}
				if (typeIndex >= static_cast<int>(CountryType::NONE) || typeIndex < 0) {
					viewData.isActionRequested = false;
					return viewData;
				}
				viewData.actionTargetCountryType = static_cast<CountryType>(typeIndex);
				return viewData;
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

	void ActionPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

}
