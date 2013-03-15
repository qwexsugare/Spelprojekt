#include "NetworkEntityAttributeMessage.h"

NetworkEntityAttributeMessage::NetworkEntityAttributeMessage()
{

}

NetworkEntityAttributeMessage::NetworkEntityAttributeMessage(unsigned int _id) : NetworkMessage(NetworkMessage::UpdateEntityAttribute)
{
	this->m_id = _id;
	this->m_health = 1;
	this->m_maxHealth = 1;
	this->m_mentalDamage = 0;
	this->m_physicalDamage = 0;
	this->m_mentalResistance = 0;
	this->m_physicalResistance = 0;
}

NetworkEntityAttributeMessage::NetworkEntityAttributeMessage(unsigned int _id, int _health, int _maxHealth, float _mentalDamage, float _physicalDamage, float _mentalResistance, float _physicalResistance) : NetworkMessage(NetworkMessage::UpdateEntityAttribute)
{
	this->m_id = _id;
	this->m_health = _health;
	this->m_maxHealth = _maxHealth;
	this->m_mentalDamage = _mentalDamage;
	this->m_physicalDamage = _physicalDamage;
	this->m_mentalResistance = _mentalResistance;
	this->m_physicalResistance = _physicalResistance;
}

NetworkEntityAttributeMessage::~NetworkEntityAttributeMessage()
{

}

unsigned int NetworkEntityAttributeMessage::getId()
{
	return this->m_id;
}

int NetworkEntityAttributeMessage::getHealth()
{
	return this->m_health;
}

int NetworkEntityAttributeMessage::getMaxHealth()
{
	return this->m_maxHealth;
}

float NetworkEntityAttributeMessage::getMentalDamage()
{
	return this->m_maxHealth;
}

float NetworkEntityAttributeMessage::getPhysicalDamage()
{
	return this->m_physicalDamage;
}

float NetworkEntityAttributeMessage::getMentalResistance()
{
	return this->m_mentalResistance;
}

float NetworkEntityAttributeMessage::getPhysicalResistance()
{
	return this->m_physicalResistance;
}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityAttributeMessage& e)
{
	return packet << *((int*)&e.m_type) << e.m_id << e.m_health << e.m_maxHealth << e.m_mentalDamage << e.m_mentalResistance << e.m_physicalDamage << e.m_physicalResistance;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEntityAttributeMessage& e)
{
	return packet >> e.m_id >> e.m_health >> e.m_maxHealth >> e.m_mentalDamage >> e.m_mentalResistance >> e.m_physicalDamage >> e.m_physicalResistance;
}