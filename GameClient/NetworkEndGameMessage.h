#pragma once
#include "networkmessage.h"
class NetworkEndGameMessage : public NetworkMessage
{
private:
	bool m_victory;

	//Statistics
public:
	NetworkEndGameMessage();
	NetworkEndGameMessage(bool _victory);
	~NetworkEndGameMessage();

	bool getVictory();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEndGameMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEndGameMessage& e);
};

