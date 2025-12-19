#pragma once
#include <string>
#include <SFML/Network.hpp>

#include "ActionPacket.h"
#include "GameState.h"
namespace TheTraitor {
union PacketData{
    /* data */
    TheTraitor::ActionPacket actionPacket;
    GameState gameState;
    std::string string;
    
    PacketData() : actionPacket() {}
    ~PacketData() {}
};

typedef struct Packet {
    //Flags
    bool actionPacket = false;
    bool ready = false;
    bool gameState = false;
    bool string = false;

    //Data
    PacketData data;
    Packet() : data() {}
} Packet;
sf::Packet& operator<<(sf::Packet& packet, const Packet& data);
sf::Packet& operator>>(sf::Packet& packet, Packet& data);
}