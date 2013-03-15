#pragma once

#include "networkmessage.h"

class NetworkReadyMessageToClient : public NetworkMessage
{
public:
	int m_playerIndex;

	NetworkReadyMessageToClient();
	NetworkReadyMessageToClient(int _playerIndex);
	~NetworkReadyMessageToClient();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkReadyMessageToClient& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkReadyMessageToClient& e);
};

