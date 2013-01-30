#pragma once
#include "networkmessage.h"
class NetworkSkillBoughtMessage : public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_resources;
public:
	NetworkSkillBoughtMessage();
	NetworkSkillBoughtMessage(unsigned int _actionId, unsigned int _resources);
	~NetworkSkillBoughtMessage();

	unsigned int getActionId();
	unsigned int getResources();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkSkillBoughtMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkSkillBoughtMessage& e);
};

