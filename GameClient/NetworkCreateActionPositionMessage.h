#pragma once

#include "networkmessage.h"
#include "DataStructures.h"

class NetworkCreateActionPositionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
	FLOAT3 m_position;
	float m_animationSpeed;
public:
	NetworkCreateActionPositionMessage();
	NetworkCreateActionPositionMessage(unsigned int _actionId, unsigned int _senderId, FLOAT3 _position, float _animationSpeed = 1.0f);
	~NetworkCreateActionPositionMessage();

	unsigned int getActionId();
	unsigned int getSenderId();
	FLOAT3 getPosition();
	float getAnimationSpeed();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionPositionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionPositionMessage& e);
};

