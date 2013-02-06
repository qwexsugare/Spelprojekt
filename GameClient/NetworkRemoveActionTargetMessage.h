#pragma once
#include "networkmessage.h"
class NetworkRemoveActionTargetMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_targetId;
public:
	NetworkRemoveActionTargetMessage();
	NetworkRemoveActionTargetMessage(unsigned int _actionId, unsigned int _targetId);
	~NetworkRemoveActionTargetMessage();

	unsigned int getActionId();
	unsigned int getTargetId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkRemoveActionTargetMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkRemoveActionTargetMessage& e);	
};

