#pragma once
#include "networkmessage.h"
class NetworkCreateActionMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_senderId;
public:
	NetworkCreateActionMessage();
	NetworkCreateActionMessage(unsigned int _actionId, unsigned int _senderId);
	~NetworkCreateActionMessage();

	unsigned int getActionId();
	unsigned int getSenderId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkCreateActionMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkCreateActionMessage& e);
};

