#pragma once
#include "networkmessage.h"

class NetworkUseActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_targetId;
	unsigned int m_index;
public:
	NetworkUseActionTargetMessage();
	NetworkUseActionTargetMessage(unsigned int m_actionId, unsigned int m_targetId, unsigned int _index);
	~NetworkUseActionTargetMessage();

	unsigned int getActionId();
	unsigned int getTargetId();
	unsigned int getIndex();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionTargetMessage& e);	
};

