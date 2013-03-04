#pragma once

#include "networkmessage.h"

class NetworkStartGameMessage :
	public NetworkMessage
{
public:
	NetworkStartGameMessage();
	~NetworkStartGameMessage();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkStartGameMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkStartGameMessage& e);
};

