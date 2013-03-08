#pragma once

#include "Datastructures.h"
#include "networkmessage.h"

class NetworkRemoveActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_targetId;
	FLOAT3 m_position;
public:
	NetworkRemoveActionTargetMessage();
	NetworkRemoveActionTargetMessage(unsigned int _actionId, unsigned int _targetId, FLOAT3 _position = FLOAT3(0.0f, 0.0f, 0.0f));
	~NetworkRemoveActionTargetMessage();

	unsigned int getActionId();
	unsigned int getTargetId();
	FLOAT3 getPosition();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveActionTargetMessage& e);	
};

