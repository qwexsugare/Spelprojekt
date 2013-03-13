#pragma once

#include "NetworkMessage.h"
#include "DataStructures.h"

class NetworkCreateActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
	unsigned int m_targetId;
	FLOAT3 m_position;
	float m_animationSpeed;
public:
	NetworkCreateActionTargetMessage();
	NetworkCreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId, FLOAT3 _position, float _animationSpeed = 1.0f);
	~NetworkCreateActionTargetMessage();

	unsigned int getActionId();
	unsigned int getSenderId();
	unsigned int getTargetId();
	FLOAT3 getPosition();
	float getAnimationSpeed();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionTargetMessage& e);
};