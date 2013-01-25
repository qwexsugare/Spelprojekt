#pragma once

#include "NetworkMessage.h"

class NetworkRemoveEntityMessage : public NetworkMessage
{
private:
	unsigned int m_entityId;
public:
	NetworkRemoveEntityMessage();
	NetworkRemoveEntityMessage(unsigned int _entityId);
	~NetworkRemoveEntityMessage();

	unsigned int getEntityId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveEntityMessage& e);
};

