#pragma once
#include "networkmessage.h"
class NetworkUseActionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_index;
public:
	NetworkUseActionMessage();
	NetworkUseActionMessage(unsigned int _actionId, unsigned int _index);
	~NetworkUseActionMessage();

	unsigned int getActionId();
	unsigned int getIndex();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkUseActionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkUseActionMessage& e);	
};

