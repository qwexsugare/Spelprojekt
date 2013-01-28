#pragma once

#include "networkmessage.h"
#include "DataStructures.h"

class NetworkCreateActionPositionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
	FLOAT3 m_position;
public:
	NetworkCreateActionPositionMessage();
	NetworkCreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position);
	~NetworkCreateActionPositionMessage();

	unsigned int getActionId();
	unsigned int getSenderId();
	FLOAT3 getPosition();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionPositionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionPositionMessage& e);
};

