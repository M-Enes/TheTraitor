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
    STRING
};

sf::Packet& operator<<(sf::Packet& packet, const PacketType& type);
sf::Packet& operator>>(sf::Packet& packet, PacketType& type);
}