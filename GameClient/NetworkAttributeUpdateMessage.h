#pragma once

#include "networkmessage.h"

class NetworkAttributeUpdateMessage : public NetworkMessage
{
private:
	int m_strength;
	int m_agility;
	int m_wits;
	int m_fortitude;
public:
	NetworkAttributeUpdateMessage();
	NetworkAttributeUpdateMessage(int _strength, int _agility, int _wits, int _fortitude);
	~NetworkAttributeUpdateMessage();

	int getStrength();
	int getAgility();
	int getWits();
	int getFortitude();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkAttributeUpdateMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkAttributeUpdateMessage& e);
};

