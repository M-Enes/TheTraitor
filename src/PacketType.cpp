#include "PacketType.h"

namespace TheTraitor {
	sf::Packet& operator<<(sf::Packet& packet, const PacketType& type)
	{
		return packet << static_cast<int>(type);
	}
	sf::Packet& operator>>(sf::Packet& packet, PacketType& type)
	{
		int x;
		packet >> x;
		type = PacketType(x);
		return packet;
	}
}