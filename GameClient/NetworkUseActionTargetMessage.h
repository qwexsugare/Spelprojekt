#pragma once
#include "networkmessage.h"

class NetworkUseActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_targetId;
public:
	NetworkUseActionTargetMessage();
	NetworkUseActionTargetMessage(unsigned int m_actionId, unsigned int m_targetId);
	~NetworkUseActionTargetMessage();

	unsigned int getActionId();
	unsigned int getTargetId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionTargetMessage& e);	
};

