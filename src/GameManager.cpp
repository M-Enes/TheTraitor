#include <iostream>
#include <algorithm>
#include <SFML/Network.hpp>

#include "GameManager.h"
#include "GameHost.h"
#include "PacketType.h"
#include "GameState.h"

TheTraitor::GameManager::GameManager() : currentPhaseIndex(0) {

}

void TheTraitor::GameManager::update() {
    switch(state.currentPhase){
        case MENU: {
            // Waiting for players to connect
            break;
        }
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
                            }
                        }
                    }
                }
            }

            // All players are ready, start the game
            state.currentPhase = ACTION_PHASE;
            isGameStarted = true;

            // Send updated game state to all players
            for (auto& player : state.players) {
                sf::TcpSocket* socket = player.getSocket();
                GameState gameState;
                PacketType gameStatePacketType = PacketType::GAMESTATE;
                sf::Packet gameStatePacket;
                gameStatePacket << gameStatePacketType;
                gameState.currentPhase = state.currentPhase;
                gameState.players = state.players;
                gameStatePacket << gameState;
                if (socket->send(gameStatePacket) != sf::Socket::Status::Done)
                {
                    //error
                }
            }

            break;
        }
        case DISCUSSION_PHASE: {
            // Allow players to discuss
            break;
        }
        case ACTION_PHASE: {
            // Receive actions from players
            std::vector<ActionPacket> actionPackets;
            for (auto& player : state.players) {
                sf::TcpSocket* socket = player.getSocket();
                sf::Packet packet;
                if (socket->receive(packet) == sf::Socket::Status::Done) {
                    PacketType packetType;
                    packet >> packetType;
                    if (packetType == PacketType::ACTION_PACKET) {
                        ActionPacket actionPacket;
                        packet >> actionPacket;
                        actionPackets.push_back(actionPacket);
                    }
                }
            }

            // Process actions
            for (const auto& actionPacket : actionPackets) {
                processAction(actionPacket);
            }

            
            state.currentPhase = RESOLUTION_PHASE;

            // Send updated game state to all players
            for (auto& player : state.players) {
                sf::TcpSocket* socket = player.getSocket();
                GameState gameState;
                PacketType gameStatePacketType = PacketType::GAMESTATE;
                sf::Packet gameStatePacket;
                gameStatePacket << gameStatePacketType;
                gameState.currentPhase = state.currentPhase;
                gameState.players = state.players;
                gameStatePacket << gameState;
                if (socket->send(gameStatePacket) != sf::Socket::Status::Done) {
                    //error
                }
            }

            break;
        }
        case RESOLUTION_PHASE: {
            // Process actions and update game state
            state.currentPhase = DISCUSSION_PHASE;

            // Send updated game state to all players
            for (auto& player : state.players) {
                sf::TcpSocket* socket = player.getSocket();
                GameState gameState;
                PacketType gameStatePacketType = PacketType::GAMESTATE;
                sf::Packet gameStatePacket;
                gameStatePacket << gameStatePacketType;
                gameState.currentPhase = state.currentPhase;
                gameState.players = state.players;
                gameStatePacket << gameState;
                if (socket->send(gameStatePacket) != sf::Socket::Status::Done) {
                    //error
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

void TheTraitor::GameManager::processAction(ActionPacket actionPacket) {
    
}

void TheTraitor::GameManager::goToNextPhase() {
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