#include "PacketType.h"
#include "ActionPacket.h"

namespace TheTraitor {
	sf::Packet& operator<<(sf::Packet& packet, const PacketType& type){
		return packet << static_cast<int>(type);
	}

	sf::Packet& operator>>(sf::Packet& packet, PacketType& type)
	{
		int x;
		packet >> x;
		type = PacketType(x);
		return packet;
	}

	sf::Packet& operator<<(sf::Packet& packet, ActionPacket& actionPacket) {
		packet << static_cast<int>(actionPacket.actionType) << actionPacket.sourceID << actionPacket.targetID;
		return packet;
	}

	sf::Packet& operator>>(sf::Packet& packet, ActionPacket& actionPacket) {
		int actionTypeValue = 0;
		packet >> actionTypeValue >> actionPacket.sourceID >> actionPacket.targetID;
		actionPacket.actionType = static_cast<ActionType>(actionTypeValue);
		return packet;
	}

	sf::Packet& operator<<(sf::Packet& packet, GameState& gameState) {
		packet << static_cast<int>(gameState.currentPhase);
		packet << static_cast<int>(gameState.players.size());
		for (const auto& player : gameState.players) {
			packet << player.getName();
			packet << player.getPlayerID();
			packet << player.getAvatarID();
			packet << player.getCountry()->getEconomy();
			packet << player.getCountry()->getHealth();
			packet << player.getCountry()->getEducation();
			packet << player.getCountry()->isDestroyed();
		}
		return packet;
	}

	sf::Packet& operator>>(sf::Packet& packet, GameState& gameState) {
		int phaseValue = 0;
		packet >> phaseValue;
		gameState.currentPhase = static_cast<GamePhase>(phaseValue);

		int playerCount = 0;
		packet >> playerCount;
		for (int i = 0; i < playerCount; ++i) {
			bool playerSet = false;
			std::string playerName;
			int playerID, avatarID;
			int economy, health, education;
			bool destroyed;

			packet >> playerName;
			packet >> playerID;
			packet >> avatarID; // AvatarID
			packet >> economy;
			packet >> health;
			packet >> education;
			packet >> destroyed;



			for(unsigned long int j = 0; j < gameState.players.size(); ++j) {
				if (gameState.players[j].getPlayerID() == playerID) {
					playerSet = true;
					gameState.players[j].setName(playerName);
					gameState.players[j].setAvatarID(avatarID);
					gameState.players[j].getCountry()->setEconomy(economy);
					gameState.players[j].getCountry()->setHealth(health);
					gameState.players[j].getCountry()->setEducation(education);
					gameState.players[j].getCountry()->setDestroyed(destroyed);
					break;
				}
			}

			if (!playerSet) {
				Country* country = new Country(economy, health, education);
				country->setDestroyed(destroyed);
				Player newPlayer(playerName, country);
				newPlayer.setSocket(nullptr); // No socket info in GameState packet
				gameState.players.push_back(newPlayer);
			}

		}
		return packet;
	}

}