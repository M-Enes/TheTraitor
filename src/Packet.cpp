#include "Packet.h"

#include <SFML/Network.hpp>
#include <cstring>

namespace TheTraitor {

sf::Packet& operator<<(sf::Packet& packet, const Packet& data) {
    packet << data.actionPacket << data.ready << data.gameState << data.string;
    if (data.actionPacket) {
        char* dataPtr = new char[sizeof(ActionPacket)];
        std::memcpy(dataPtr, &data.data.actionPacket, sizeof(ActionPacket));
        packet << dataPtr;
        delete[] dataPtr;
    }
    if (data.gameState) {
        char* dataPtr = new char[sizeof(GameState)];
        std::memcpy(dataPtr, &data.data.gameState, sizeof(GameState));
        packet << dataPtr;
        delete[] dataPtr;
    }
    if (data.string) {
        packet << data.data.string;
    }
    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Packet& data) {
    packet >> data.actionPacket >> data.ready >> data.gameState >> data.string;
    if (data.actionPacket) {
        char* dataPtr = new char[sizeof(ActionPacket)];
        packet >> dataPtr;
        std::memcpy(&data.data.actionPacket, dataPtr, sizeof(ActionPacket));
        delete[] dataPtr;
    }
    if (data.gameState) {
        char* dataPtr = new char[sizeof(GameState)];
        packet >> dataPtr;
        std::memcpy(&data.data.gameState, dataPtr, sizeof(GameState));
        delete[] dataPtr;
    }
    if (data.string) {
        packet >> data.data.string;
    }
    return packet;
}

} // namespace TheTraitor