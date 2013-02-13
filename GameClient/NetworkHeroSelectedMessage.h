#pragma once

#include "networkmessage.h"

class NetworkHeroSelectedMessage :
	public NetworkMessage
{
private:
	int m_heroId;
	int m_playerId;
public:
	NetworkHeroSelectedMessage();
	NetworkHeroSelectedMessage(int _heroId, int _playerId);
	~NetworkHeroSelectedMessage();

	int getHeroId()const { return m_heroId; }
	int getPlayerId()const { return m_playerId; }

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkHeroSelectedMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkHeroSelectedMessage& e);
};