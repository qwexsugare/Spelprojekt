#pragma once

#include "networkmessage.h"
#include "DataStructures.h"

class NetworkUseActionPositionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_index;
	FLOAT3 m_position;
public:
	NetworkUseActionPositionMessage();
	NetworkUseActionPositionMessage(unsigned int _actionId, FLOAT3 _position, unsigned int _index);
	~NetworkUseActionPositionMessage();

	unsigned int getActionId();
	FLOAT3 getPosition();
	unsigned int getIndex();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionPositionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionPositionMessage& e);	
};

