#pragma once
#include "networkmessage.h"
class NetworkUseActionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
public:
	NetworkUseActionMessage();
	NetworkUseActionMessage(unsigned int _actionId);
	~NetworkUseActionMessage();

	unsigned int getActionId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionMessage& e);	
};

