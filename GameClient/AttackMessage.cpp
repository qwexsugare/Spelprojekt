#include "AttackMessage.h"

AttackMessage::AttackMessage()
{

}

AttackMessage::AttackMessage(unsigned int _senderId, FLOAT3 _targetPos)
{
	this->m_senderId = _senderId;
	this->m_targetPos = _targetPos;
}

AttackMessage::~AttackMessage()
{

}

void AttackMessage::setTargetPos(FLOAT3 _targetPos)
{
	this->m_targetPos = _targetPos;
}

FLOAT3 AttackMessage::getTargetPos()
{
	return this->m_targetPos;
}

unsigned int AttackMessage::getSenderId()
{
	return this->m_senderId;
}

sf::Packet& operator<<(sf::Packet& packet,const AttackMessage& e)
{
	return packet<<"ATTACK"<<e.m_senderId<<e.m_targetPos.x<<e.m_targetPos.y<<e.m_targetPos.z;
}

sf::Packet& operator>>(sf::Packet& packet, AttackMessage& e)
{
	return packet>>e.m_senderId>>e.m_targetPos.x>>e.m_targetPos.y>>e.m_targetPos.z;
}