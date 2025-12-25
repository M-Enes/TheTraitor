#include <iostream>
#include <algorithm>
#include <SFML/Network.hpp>
#include <random>

#include "GameManager.h"
#include "GameHost.h"
#include "Common/PacketType.h"
#include "Common/GameState.h"

#include "Common/Role.h"

#include "Common/Actions.h"
#include "Common/ActionPacket.h"


namespace TheTraitor {


	GameManager::GameManager() : currentPhaseIndex(0) {

	}

	void GameManager::update() {
		switch (state.currentPhase) {
		case LOBBY: {
			// All players are ready, start the game
			
			std::cout << "All players connected. Starting the game..." << std::endl;
			state.currentPhase = ACTION_PHASE;
			isGameStarted = true;

			// Choose the traitor randomly
			std::srand(time(nullptr));
			traitorIndex = std::rand() % 5;
			state.players[traitorIndex].setRole(new Traitor()); // Just a placeholder, set the actual Role object later

			// Set the role of the traitor to the innocent temporarily


			// Send updated game state to all players
			sendGameStateToAllPlayers();
			currentPhaseTimer.restart();

			break;
		}
		case DISCUSSION_PHASE: {
			// Allow players to discuss
			std::vector<int> readyPlayers;

			while (readyPlayers.size() < state.players.size()) {
				// Check for ready packets from all players
				for (auto& player : state.players) {
					sf::TcpSocket* socket = player.getSocket();
					sf::Packet packet;
					if (socket->receive(packet) == sf::Socket::Status::Done) {
						PacketType packetType;
						packet >> packetType;
						if (packetType == PacketType::READY) {
							if (std::find(readyPlayers.begin(), readyPlayers.end(), player.getPlayerID()) == readyPlayers.end()) {
								readyPlayers.push_back(player.getPlayerID());
								std::cout << "Player " << player.getPlayerID() << " is ready." << std::endl;
							}
						}
					}
				}
				if (currentPhaseTimer.getElapsedTime().asSeconds() >= 120) {
					break;
				}
			}

			// All players are ready, start the game
			state.currentPhase = ACTION_PHASE;
			std::cout << "All players are ready. Moving to ACTION_PHASE..." << std::endl;
			isGameStarted = true;

			// Send updated game state to all players
			sendGameStateToAllPlayers();
			currentPhaseTimer.restart();

			break;
		}
		case ACTION_PHASE: {

			// Receive actions from players
			std::vector<ActionPacket> actionPackets;
			ActionPacket secretAction;
			std::vector<int> processedPlayerIDs;
			bool secretyActionsProcessed = false;
			while (actionPackets.size() < state.players.size()) {
				for (auto& player : state.players) {
					sf::TcpSocket* socket = player.getSocket();
					sf::Packet packet;
					if (socket->receive(packet) == sf::Socket::Status::Done) {
						PacketType packetType;
						packet >> packetType;
						if (packetType == PacketType::ACTION_PACKET) {
							ActionPacket actionPacket;
							packet >> actionPacket;

							if (actionPacket.actionType == ActionType::SpreadPlague || actionPacket.actionType == ActionType::DestroySchool || actionPacket.actionType == ActionType::SabotageFactory) {
								if (!secretyActionsProcessed && actionPacket.sourceID == traitorIndex) {
									secretAction = actionPacket;
									secretyActionsProcessed = true;
								}
								continue;
							}

							if (std::find(processedPlayerIDs.begin(), processedPlayerIDs.end(), actionPacket.sourceID) == processedPlayerIDs.end()) {
								processedPlayerIDs.push_back(actionPacket.sourceID);
								actionPackets.push_back(actionPacket);
							}
						}
					}
				}
				if (currentPhaseTimer.getElapsedTime().asSeconds() >= 90) {
					break;
				}
			}

			std::cout << "All actions received. Processing actions..." << std::endl;

			// Process actions
			for (const auto& actionPacket : actionPackets) {
				processAction(actionPacket);
			}

			// Process secret action of the traitor
			if (secretyActionsProcessed) {
				processAction(secretAction);
			}

			// Move to resolution phase
			state.currentPhase = RESOLUTION_PHASE;

			std::cout << "All actions are processed. Moving to RESOLUTION_PHASE..." << std::endl;

			// Send updated game state to all players
			sendGameStateToAllPlayers();
			currentPhaseTimer.restart();

			break;
		}
		case RESOLUTION_PHASE: {
			// Process actions and update game state
			if (state.players[traitorIndex].getCountry()->isDestroyed()) {
				// Traitor lost, innocents win
				state.currentPhase = WIN; // win for innocents
				sendGameStateToAllPlayers();
				state.currentPhase = MENU;
				std::cout << "Innocents win! The traitor's country is destroyed." << std::endl;
			}
			else {
				int destroyedCountries = 0;
				for (const auto& player : state.players) if (player.getCountry()->isDestroyed()) destroyedCountries++;
				if (destroyedCountries == state.players.size() - 1) {
					// Traitor wins
					state.currentPhase = GAMEOVER; // gamover for innocents
					sendGameStateToAllPlayers();
					state.currentPhase = MENU;
					std::cout << "Traitor wins! All innocent countries are destroyed." << std::endl;
				}
				else {
					// Continue game
					state.currentPhase = DISCUSSION_PHASE;
					std::cout << "Game continues. Moving to DISCUSSION_PHASE..." << std::endl;

					// Send updated game state to all players
					sendGameStateToAllPlayers();

					break;
				}

			}
			break;

		}

		default: {
			// Do nothing
			break;
		}
		}
	}

	void GameManager::processAction(ActionPacket actionPacket) {
		Action* action = nullptr;
		// Find the action corresponding to actionPacket.actionType
		switch (actionPacket.actionType) {
		case ActionType::TradePact:
			action = new TradePact();
			std::cout << "The player " << actionPacket.sourceID << " performed TradePact on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::TradeEmbargo:
			action = new TradeEmbargo();
			std::cout << "The player " << actionPacket.sourceID << " performed TradeEmbargo on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::JointResearch:
			action = new JointResearch();
			std::cout << "The player " << actionPacket.sourceID << " performed JointResearch on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::SpreadMisinfo:
			action = new SpreadMisinfo();
			std::cout << "The player " << actionPacket.sourceID << " performed SpreadMisinfo on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::HealthAid:
			action = new HealthAid();
			std::cout << "The player " << actionPacket.sourceID << " performed HealthAid on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::PoisonResources:
			action = new PoisonResources();
			std::cout << "The player " << actionPacket.sourceID << " performed PoisonResources on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::SpreadPlague:
			action = new SpreadPlague();
			std::cout << "The player " << actionPacket.sourceID << " performed SpreadPlague on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::DestroySchool:
			action = new DestroySchool();
			std::cout << "The player " << actionPacket.sourceID << " performed DestroySchool on player " << actionPacket.targetID << "." << std::endl;
			break;
		case ActionType::SabotageFactory:
			action = new SabotageFactory();
			std::cout << "The player " << actionPacket.sourceID << " performed SabotageFactory on player " << actionPacket.targetID << "." << std::endl;
			break;
		default:
			break;
		}

		int sourceIndex = 0, targetIndex = 0, index = 0;

		for (const auto& player : state.players) {
			if (player.getPlayerID() == actionPacket.sourceID) {
				sourceIndex = index;
			}

			if (player.getPlayerID() == actionPacket.targetID) {
				targetIndex = index;
			}

			index++;
		}

		action->execute(
			state.players[sourceIndex],
			state.players[targetIndex]
		);

		std::cout << "Action executed: " << action->getLogMessage(state.players[sourceIndex], state.players[targetIndex]) << std::endl;

		delete action;
	}

	void GameManager::run() {
		GameHost host;
		host.establishConnectionWithClients(state);
		while (true) {
			update();
		}
	}

	void GameManager::sendGameStateToAllPlayers() {
		for (auto& player : state.players) {
			sf::TcpSocket* socket = player.getSocket();
			GameState stateToSend;
			PacketType gameStatePacketType = PacketType::GAMESTATE;
			sf::Packet gameStatePacket;
			gameStatePacket << gameStatePacketType;
			stateToSend.currentPhase = state.currentPhase;
			if (state.currentPhase == WIN || state.currentPhase == GAMEOVER) {
				// Reveal the traitor's role at the end of the game
				stateToSend.players = state.players;
				gameStatePacket << stateToSend;
				if (socket->send(gameStatePacket) != sf::Socket::Status::Done)
				{
					//error
				}
			}
			else {
				// Hide the traitor's role during the game
				Role* originalRole = state.players.at(traitorIndex).getRole();
				Innocent* tempRole = new Innocent(); //
				state.players.at(traitorIndex).setRole(tempRole); // Temporarily set to Innocent
				stateToSend.players = state.players;
				state.players.at(traitorIndex).setRole(originalRole); // Restore original role
				gameStatePacket << stateToSend;
				delete tempRole; // Clean up the temporary role object
				if (socket->send(gameStatePacket) != sf::Socket::Status::Done)
				{
					//error
				}
			}
		}

		std::cout << "Game state sent to all players." << std::endl;
	}
}