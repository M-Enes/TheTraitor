#include "GameManager.h"

#include <iostream>
#include <algorithm>
#include <SFML/Network.hpp>
#include <random>


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
		std::vector<ActionPacket> actionPackets;
		switch (state.currentPhase) {
			case LOBBY: {
				std::cout << "All players connected. Starting the game..." << std::endl;
				state.currentPhase = ACTION_PHASE;
				
				// Choose the traitor randomly
				std::srand(time(nullptr));
				traitorIndex = std::rand() % 5;
				for (int i = 0; i < state.players.size(); ++i) {
					if (i == traitorIndex) {
						Role* traitorRole = new Traitor();
						state.players[i].setRole(traitorRole);
						std::cout << "Player " << state.players[i].getPlayerID() << " is the Traitor." << std::endl;
					}
					else {
						Role* innocentRole = new Innocent();
						state.players[i].setRole(innocentRole);
					}
				}

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
					if (currentPhaseTimer.getElapsedTime().asSeconds() >= 120) break;
				}

				// All players are ready, start the game
				state.currentPhase = ACTION_PHASE;
				std::cout << "All players are ready. Moving to ACTION_PHASE..." << std::endl;
				
				// Send updated game state to all players
				sendGameStateToAllPlayers();
				currentPhaseTimer.restart();

				break;
			}
			case ACTION_PHASE: {
				// Receive actions from players
				ActionPacket secretAction;
				std::vector<int> handledPlayerIDs;
				bool secretyActionsReceived = false;

				int alivePlayersCount = 0;
				for (const auto& player : state.players) {
					if (!player.getCountry()->isDestroyed()) {
						alivePlayersCount++;
					}
				}

				std::cout << "Alive players count: " << alivePlayersCount << std::endl;

				while (actionPackets.size() < alivePlayersCount) {
					if (selector.wait(sf::milliseconds(100))) {
						for (auto& player : state.players) {
							sf::TcpSocket* socket = player.getSocket();
							if (selector.isReady(*socket)) {
								sf::Packet packet;
								if (socket->receive(packet) == sf::Socket::Status::Done) {
									// std::cout << "Received packet from player socket " << player.getPlayerID() << std::endl;
									PacketType packetType;
									packet >> packetType;
									if (packetType == PacketType::ACTION_PACKET) {
										ActionPacket actionPacket;
										packet >> actionPacket;
										std::cout << "Received ACTION_PACKET from SourceID: " << actionPacket.sourceID << " (ActionType: " << (int)actionPacket.actionType << ")" << std::endl;

										// Check if the source player is actually alive (server-side validation)
										bool isSourceAlive = false;
										for (const auto& p : state.players) {
											if (p.getPlayerID() == actionPacket.sourceID && !p.getCountry()->isDestroyed()) {
												isSourceAlive = true;
												break;
											}
										}
										// If source is dead, ignore this packet (unless we want to log it)
										if (!isSourceAlive) {
											std::cout << "Ignored action from DEAD player " << actionPacket.sourceID << std::endl;
											continue;
										}

										if (actionPacket.actionType == ActionType::SpreadPlague || actionPacket.actionType == ActionType::DestroySchool || actionPacket.actionType == ActionType::SabotageFactory) {
											int traitorID = state.players[traitorIndex].getPlayerID();
											if (!secretyActionsReceived && actionPacket.sourceID == traitorID) {
												secretAction = actionPacket;
												secretyActionsReceived = true;
												std::cout << "Secret action received from traitor." << std::endl;
											}
											continue;
										}

										if (std::find(handledPlayerIDs.begin(), handledPlayerIDs.end(), actionPacket.sourceID) == handledPlayerIDs.end()) {
											handledPlayerIDs.push_back(actionPacket.sourceID);
											actionPackets.push_back(actionPacket);
											std::cout << "Action accepted. Progress: " << actionPackets.size() << "/" << alivePlayersCount << std::endl;
										} else {
											std::cout << "Ignored duplicate action from player " << actionPacket.sourceID << std::endl;
										}
									} else {
										std::cout << "Received non-action packet: " << (int)packetType << std::endl;
									}
								}
							}
						}
					}
					
					if (currentPhaseTimer.getElapsedTime().asSeconds() >= 90) {
						std::cout << "Action Phase Timeout (90s) reached." << std::endl;
						break;
					}
				}

				std::cout << "All actions received. Processing actions..." << std::endl;

				// Process actions
				for (const auto& actionPacket : actionPackets) {
					processAction(actionPacket);
				}

				// Process secret action of the traitor
				if (secretyActionsReceived) {
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
					unsigned long int destroyedCountries = 0;
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
						sendActionPacketToAllPlayers(actionPackets);

						// Clear the action packets vector
						actionPackets.clear();
					}
				}
				break;
			}
			case MENU:
			case GAMEOVER:
			case WIN:
			case NONE:
			default:
				// Do nothing
				break;
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
			if (player.getPlayerID() == actionPacket.sourceID) sourceIndex = index;
			if (player.getPlayerID() == actionPacket.targetID) targetIndex = index;
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
		for (auto& player : state.players) {
			selector.add(*player.getSocket());
		}
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
			if (state.currentPhase == WIN || state.currentPhase == GAMEOVER || player.getPlayerID() == state.players[traitorIndex].getPlayerID()) {
				// Reveal the traitor's role at the end of the game, and send full state to the traitor
				stateToSend.players = state.players;
				gameStatePacket << stateToSend;
				if (socket->send(gameStatePacket) != sf::Socket::Status::Done) {				
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
					if (socket->send(gameStatePacket) != sf::Socket::Status::Done) {
					//error
				}
			}
		}

		std::cout << "Game state sent to all players." << std::endl;
	}

	void GameManager::sendActionPacketToAllPlayers(std::vector<ActionPacket> actionPackets) {	
		for (auto& player : state.players) {
			sf::TcpSocket* socket = player.getSocket();

			// Send the number of action packets first
			PacketType actionPacketCountType = PacketType::INT;
			sf::Packet actionPacketCountPacket;
			actionPacketCountPacket << actionPacketCountType;
			actionPacketCountPacket << static_cast<int>(actionPackets.size());
			if (socket->send(actionPacketCountPacket) != sf::Socket::Status::Done) {
				//error
			}

			// Send each action packet
			for (auto& actionPacket : actionPackets) {
				PacketType actionPacketType = PacketType::ACTION_PACKET;
				sf::Packet packet;
				packet << actionPacketType;
				packet << actionPacket;
				if (socket->send(packet) != sf::Socket::Status::Done){
					//error
				}
			}
		}

		std::cout << "Action packets sent to all players." << std::endl;
	}

}