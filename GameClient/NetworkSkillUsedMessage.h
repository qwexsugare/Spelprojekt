#pragma once
#include "networkmessage.h"
class NetworkSkillUsedMessage :
	public NetworkMessage
{
private:
	unsigned int m_actionId;
	unsigned int m_actionIndex;
	float m_cooldown;
public:
	NetworkSkillUsedMessage();
	NetworkSkillUsedMessage(unsigned int _actionId, unsigned int _actionIndex, float _cooldown);
	~NetworkSkillUsedMessage(void);

	unsigned int getActionId();
	unsigned int getActionIndex();
	float getCooldown();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkSkillUsedMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkSkillUsedMessage& e);
};

