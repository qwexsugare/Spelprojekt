#pragma once

#include "networkmessage.h"

class NetworkSelectHeroMessage :
	public NetworkMessage
{
private:
	int m_heroId;
public:
	NetworkSelectHeroMessage();
	NetworkSelectHeroMessage(int _heroId);
	~NetworkSelectHeroMessage();

	int getHeroId()const { return m_heroId; }

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkSelectHeroMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkSelectHeroMessage& e);
};

