#ifndef ATTACK_ENTITY_MESSAGE_H
#define ATTACK_ENTITY_MESSAGE_H

#include <SFML\Network.hpp>

class AttackEntityMessage
{
private:
	unsigned int m_senderId;
	unsigned int m_targetId;
public:
	AttackEntityMessage();
	AttackEntityMessage(unsigned int _senderId, unsigned int _targetId);

	unsigned int getSenderId();
	unsigned int getTargetId();

	friend sf::Packet& operator<<(sf::Packet& packet,const AttackEntityMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, AttackEntityMessage& e);
};

#endif