#pragma once
#include <string>
#include <SFML/Network.hpp>

#include "ActionPacket.h"
#include "GameState.h"
namespace TheTraitor {

enum class PacketType {
    UNKNOWN,
    ACTION_PACKET,
    READY,
    GAMESTATE,
    STRING,
    INT
};

sf::Packet& operator<<(sf::Packet& packet, const PacketType& type);
sf::Packet& operator>>(sf::Packet& packet, PacketType& type);
sf::Packet& operator<<(sf::Packet& packet, ActionPacket& actionPacket);
sf::Packet& operator>>(sf::Packet& packet, ActionPacket& actionPacket);
sf::Packet& operator<<(sf::Packet& packet, GameState& gameState);
sf::Packet& operator>>(sf::Packet& packet, GameState& gameState);
} // namespace TheTraitor