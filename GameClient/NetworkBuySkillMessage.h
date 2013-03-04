#pragma once

#include "networkmessage.h"

class NetworkBuySkillMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
public:
	NetworkBuySkillMessage();
	NetworkBuySkillMessage(unsigned int _actionId);
	~NetworkBuySkillMessage();

	unsigned int getActionId();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkBuySkillMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkBuySkillMessage& e);
};

