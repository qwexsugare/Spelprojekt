#pragma once
#include "NetworkMessage.h"
class NetworkUpdateEntityHealth: public NetworkMessage
{
private:
	int m_id;
	int health;
public:
	NetworkUpdateEntityHealth(void);
	NetworkUpdateEntityHealth(int m_id, int health);
	~NetworkUpdateEntityHealth(void);
	int getHealth();
	int getId();
	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUpdateEntityHealth& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUpdateEntityHealth& e);
};

