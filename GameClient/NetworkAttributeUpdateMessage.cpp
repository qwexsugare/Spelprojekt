#include "NetworkAttributeUpdateMessage.h"

NetworkAttributeUpdateMessage::NetworkAttributeUpdateMessage()
{

}

NetworkAttributeUpdateMessage::NetworkAttributeUpdateMessage(int _strength, int _agility, int _wits, int _fortitude)
{
	this->m_strength = _strength;
	this->m_agility = _agility;
	this->m_wits = _wits;
	this->m_fortitude = _fortitude;
}

NetworkAttributeUpdateMessage::~NetworkAttributeUpdateMessage()
{

}

int NetworkAttributeUpdateMessage::getStrength()
{
	return this->m_strength;
}

int NetworkAttributeUpdateMessage::getAgility()
{
	return this->m_agility;
}

int NetworkAttributeUpdateMessage::getWits()
{
	return this->m_wits;
}

int NetworkAttributeUpdateMessage::getFortitude()
{
	return this->m_fortitude;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkAttributeUpdateMessage& e)
{
	return packet<<*((int*)&e.m_type)<<e.m_strength<<e.m_agility<<e.m_wits<<e.m_fortitude;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkAttributeUpdateMessage& e)
{
	return packet>>e.m_strength>>e.m_agility>>e.m_wits>>e.m_fortitude;
}