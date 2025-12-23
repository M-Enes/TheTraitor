#include <iostream>
#include <algorithm>
#include <SFML/Network.hpp>
#include <random>

#include "GameManager.h"
#include "GameHost.h"
#include "PacketType.h"
#include "GameState.h"

#include "Role.h"

#include "Actions.h"
#include "ActionPacket.h"


TheTraitor::GameManager::GameManager() : currentPhaseIndex(0) {

}

void TheTraitor::GameManager::update() {
    switch(state.currentPhase){
        case LOBBY: {
            // Waiting for all players to be ready
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
                                sendGameStateToAllPlayers();
                            }
                        }
                    }
                }
            }

            // All players are ready, start the game
            state.currentPhase = ACTION_PHASE;
            isGameStarted = true;

            // Choose the traitor randomly
            std::srand(time(nullptr));
            int traitorIndex = std::rand() % state.players.size();
            state.players[traitorIndex].setRole(new TheTraitor::Traitor()); // Just a placeholder, set the actual Role object later

            // Set the role of the traitor to the innocent temporarily
            

            // Send updated game state to all players
            sendGameStateToAllPlayers();

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
                            }
                        }
                    }
                }
            }

            // All players are ready, start the game
            state.currentPhase = ACTION_PHASE;
            isGameStarted = true;

            // Send updated game state to all players
            sendGameStateToAllPlayers();

            break;
        }
        case ACTION_PHASE: {

            // Receive actions from players
            std::vector<ActionPacket> actionPackets;
            std::vector<int> processedPlayerIDs;
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
                        if (std::find(processedPlayerIDs.begin(), processedPlayerIDs.end(), actionPacket.sourceID) == processedPlayerIDs.end()) {
                            processedPlayerIDs.push_back(actionPacket.sourceID);
                            actionPackets.push_back(actionPacket);
                        }
                    }
                }
            }
            }
            

            // Process actions
            for (const auto& actionPacket : actionPackets) {
                processAction(actionPacket);
            }

            // Move to resolution phase
            state.currentPhase = RESOLUTION_PHASE;

            // Send updated game state to all players
            sendGameStateToAllPlayers();

            break;
        }
        case RESOLUTION_PHASE: {
            // Process actions and update game state
            state.currentPhase = DISCUSSION_PHASE;

            // Send updated game state to all players
            sendGameStateToAllPlayers();

            break;
        }

        default: {
            // Do nothing
            break;
        }
    }
}

void TheTraitor::GameManager::processAction(ActionPacket actionPacket) {
    Action* action = nullptr;
    // Find the action corresponding to actionPacket.actionType
    switch (actionPacket.actionType) {
            case ActionType::TradePact:
                action = new TheTraitor::TradePact();
            break;
        case ActionType::TradeEmbargo:
            action = new TheTraitor::TradeEmbargo();
            break;
        case ActionType::JointResearch:
            action = new TheTraitor::JointResearch();
            break;
        case ActionType::SpreadMisinfo:
            action = new TheTraitor::SpreadMisinfo();
            break;
        case ActionType::HealthAid:
            action = new TheTraitor::HealthAid();
            break;
        case ActionType::PoisonResources:
            action = new TheTraitor::PoisonResources();
            break;
        case ActionType::SpreadPlague:
            action = new TheTraitor::SpreadPlague();
            break;
        case ActionType::DestroySchool:
            action = new TheTraitor::DestroySchool();
            break;
        case ActionType::SabotageFactory:
            action = new TheTraitor::SabotageFactory();
            break;
        default:
            break;
    }

    action->execute(
        state.players[actionPacket.sourceID],
        state.players[actionPacket.targetID]
    );
}

void TheTraitor::GameManager::resetCurrentPhaseTimer() {
    currentPhaseTimer = std::clock();
}

void TheTraitor::GameManager::run() {
    GameHost host;
    host.establishConnectionWithClients(state);
    while(true){
        update();
    }
}

void TheTraitor::GameManager::sendGameStateToAllPlayers() {
    for (auto& player : state.players) {
        sf::TcpSocket* socket = player.getSocket();
        GameState gameState;
        PacketType gameStatePacketType = PacketType::GAMESTATE;
        sf::Packet gameStatePacket;
        gameStatePacket << gameStatePacketType;
        gameState.currentPhase = state.currentPhase;
        TheTraitor::Innocent* tempRole = new TheTraitor::Innocent();
        TheTraitor::Role* originalRole = state.players.at(traitorIndex).getRole();
        state.players.at(traitorIndex).setRole(tempRole); // Temporarily set to Innocent
        gameState.players = state.players;
        state.players.at(traitorIndex).setRole(originalRole); // Restore original role
        gameStatePacket << gameState;
        delete tempRole; // Clean up the temporary role object
        if (socket->send(gameStatePacket) != sf::Socket::Status::Done)
        {
            //error
        }
    }
}