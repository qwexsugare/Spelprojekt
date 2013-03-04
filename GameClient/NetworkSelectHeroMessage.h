#pragma once

#include "networkmessage.h"

class NetworkSelectHeroMessage :
	public NetworkMessage
{
private:
	int m_heroId;
	int m_weapon;
public:
	NetworkSelectHeroMessage();
	NetworkSelectHeroMessage(int _heroId, int _weapon);
	~NetworkSelectHeroMessage();

	int getHeroId()const { return m_heroId; }
	int getWeapon()const { return m_weapon; }

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkSelectHeroMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkSelectHeroMessage& e);
};

