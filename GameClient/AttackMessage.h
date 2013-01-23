#ifndef ATTACK_MESSAGE_H
#define ATTACK_MESSAGE_H

#include "DataStructures.h"
#include <SFML\Network.hpp>
#include <string>

class AttackMessage
{
private:
	unsigned int m_senderId;
	FLOAT3 m_targetPos;
public:
	AttackMessage();	
	AttackMessage(unsigned int _senderId, FLOAT3 _targetPos);
	~AttackMessage();
	void setTargetPos(FLOAT3 _targetPos);
	FLOAT3 getTargetPos();
	unsigned int getSenderId();

	friend sf::Packet& operator<<(sf::Packet& packet,const AttackMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, AttackMessage& e);
};

#endif