#pragma once
#include <string>
#include <SFML/Network.hpp>

#include "ActionPacket.h"
#include "GameState.h"
namespace TheTraitor {

/**
 * @brief Enumeration of packet types used for network communication.
 */
enum class PacketType {
    UNKNOWN,       ///< Unknown packet type.
    ACTION_PACKET, ///< Packet containing action details.
    READY,         ///< Packet indicating a player is ready.
    GAMESTATE,     ///< Packet containing the full game state.
    STRING,        ///< Packet containing a raw string message.
    INT            ///< Packet containing a raw integer.
};

sf::Packet& operator<<(sf::Packet& packet, const PacketType& type);
sf::Packet& operator>>(sf::Packet& packet, PacketType& type);
sf::Packet& operator<<(sf::Packet& packet, ActionPacket& actionPacket);
sf::Packet& operator>>(sf::Packet& packet, ActionPacket& actionPacket);
sf::Packet& operator<<(sf::Packet& packet, GameState& gameState);
sf::Packet& operator>>(sf::Packet& packet, GameState& gameState);
} // namespace TheTraitor