#pragma once

#include "networkmessage.h"

class NetworkReadyMessage : public NetworkMessage
{
private:
	bool m_isPorn;
public:
	NetworkReadyMessage();
	NetworkReadyMessage(bool _isPorn);
	~NetworkReadyMessage();

	bool isPorn()const { return m_isPorn; }

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkReadyMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkReadyMessage& e);
};

