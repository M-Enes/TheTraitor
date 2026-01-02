#include "Client/Phases/ResolutionPhase.h"
#include <iostream>

namespace TheTraitor {

	ResolutionPhase::ResolutionPhase(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Texture>& avatarTextures) 
		: window(window), font(font), avatarTextures(avatarTextures), 
		  viewData{ false, ActionType::TradePact, CountryType::NONE, NONE, "", 0}
	{
	}

	void ResolutionPhase::setActions(const std::vector<ActionPacket>& acts) {
		actions = acts;
		std::cout << "ResolutionPhase::setActions called with " << actions.size() << " actions." << std::endl;
	}

	void ResolutionPhase::render(const GameState& gameState, int localPlayerID, float elapsedTime, int roundCounter) {
		// std::cout << "ResolutionPhase::render called. Actions: " << actions.size() << std::endl;
		
		// Draw Title
		sf::Text title(font, "Resolution Phase", 40);
		title.setPosition({ 50, 30 });
		title.setStyle(sf::Text::Bold);
		window.draw(title);

		float startY = 100.0f;
		float gap = 60.0f;

		if (actions.empty()) {
			sf::Text noActions(font, "No public actions this round.", 30);
			noActions.setPosition({ 50, 100 });
			window.draw(noActions);
			return;
		}

		for (const auto& action : actions) {
			const Player* source = nullptr;
			const Player* target = nullptr;

			for (const auto& p : gameState.players) {
				if (p.getPlayerID() == action.sourceID) source = &p;
				if (p.getPlayerID() == action.targetID) target = &p;
			}

			if (!source || !target) {
				std::cout << "ResolutionPhase: Skipping action due to missing source or target. " 
					<< "SourceID: " << action.sourceID << ", TargetID: " << action.targetID << std::endl;
				continue;
			}

			// std::cout << "ResolutionPhase: Drawing action " << getActionName(action.actionType) << std::endl;

			float currentX = 50.0f;

			// Source Avatar
			if (source->getAvatarID() >= 0 && source->getAvatarID() < (int)avatarTextures.size()) {
				sf::Sprite sourceAvatar(avatarTextures[source->getAvatarID()]);
				sourceAvatar.setScale({ 0.25f, 0.25f });
				sourceAvatar.setPosition({ currentX, startY });
				window.draw(sourceAvatar);
			}
			currentX += 60;

			// Source Name
			sf::Text sourceName(font, source->getName(), 24);
			sourceName.setPosition({ currentX, startY + 10 });
			window.draw(sourceName);
			
			// Measure width to position next element
			currentX += sourceName.getLocalBounds().size.x + 20;

			// Action Arrow
			std::string actionStr = " -> " + getActionName(action.actionType) + " -> ";
			sf::Text actionText(font, actionStr, 24);
			actionText.setFillColor(sf::Color::Yellow);
			actionText.setPosition({ currentX, startY + 10 });
			window.draw(actionText);

			currentX += actionText.getLocalBounds().size.x + 20;

			// Target Avatar
			if (target->getAvatarID() >= 0 && target->getAvatarID() < (int)avatarTextures.size()) {
				sf::Sprite targetAvatar(avatarTextures[target->getAvatarID()]);
				targetAvatar.setScale({ 0.25f, 0.25f });
				targetAvatar.setPosition({ currentX, startY });
				window.draw(targetAvatar);
			}
			currentX += 60;

			// Target Name
			sf::Text targetName(font, target->getName(), 24);
			targetName.setPosition({ currentX, startY + 10 });
			window.draw(targetName);

			startY += gap;
		}
	}

	const ViewData& ResolutionPhase::handleInput(const InputData& inputData) {
		resetViewData();
		return viewData;
	}

	void ResolutionPhase::resetViewData() {
		viewData.isActionRequested = false;
		viewData.gotoState = NONE;
	}

	std::string ResolutionPhase::getActionName(ActionType type) {
		switch (type) {
		case ActionType::TradePact: return "Trade Pact";
		case ActionType::TradeEmbargo: return "Trade Embargo";
		case ActionType::JointResearch: return "Joint Research";
		case ActionType::SpreadMisinfo: return "Spread Misinfo";
		case ActionType::HealthAid: return "Health Aid";
		case ActionType::PoisonResources: return "Poison Resources";
		case ActionType::SpreadPlague: return "Spread Plague";
		case ActionType::DestroySchool: return "Destroy School";
		case ActionType::SabotageFactory: return "Sabotage Factory";
		default: return "Unknown";
		}
	}

}
