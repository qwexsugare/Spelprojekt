#include "AttackEntityMessage.h"

AttackEntityMessage::AttackEntityMessage()
{
	this->m_senderId = 0;
	this->m_targetId = 0;
}

AttackEntityMessage::AttackEntityMessage(unsigned int _senderId, unsigned int _targetId)
{
	this->m_senderId = _senderId;
	this->m_targetId = _targetId;
}

unsigned int AttackEntityMessage::getSenderId()
{
	return this->m_senderId;
}

unsigned int AttackEntityMessage::getTargetId()
{
	return this->m_targetId;
}

sf::Packet& operator<<(sf::Packet& packet,const AttackEntityMessage& e)
{
	return packet<<"ATTACKENTITY"<<e.m_senderId<<e.m_targetId;
}

sf::Packet& operator>>(sf::Packet& packet, AttackEntityMessage& e)
{
	return packet>>e.m_senderId>>e.m_targetId;
}