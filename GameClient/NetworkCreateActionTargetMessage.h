#pragma once

#include "NetworkMessage.h"

class NetworkCreateActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
	unsigned int m_targetId;
public:
	NetworkCreateActionTargetMessage();
	NetworkCreateActionTargetMessage(unsigned int _actionId, unsigned int _senderId, unsigned int _targetId);
	~NetworkCreateActionTargetMessage();

	unsigned int getActionId();
	unsigned int getSenderId();
	unsigned int getTargetId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionTargetMessage& e);
};

