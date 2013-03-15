#include "NetworkEntityAttributeMessage.h"

NetworkEntityAttributeMessage::NetworkEntityAttributeMessage()
{

}

NetworkEntityAttributeMessage::NetworkEntityAttributeMessage(unsigned int _id, int _strength, int _wits, int _fortitude, int _agility, int _towerConstruction,
	int _maxHealth, float _mentalDamage, float _physicalDamage, float _mentalResistance, float _physicalResistance) :
	NetworkMessage(NetworkMessage::UpdateEntityAttribute)
{
	id = _id;
	strength = _strength;
	wits = _wits;
	fortitude = _fortitude;
	agility = _agility;
	towerConstruction = _towerConstruction;
	maxHealth = _maxHealth;
	mentalDamage = _mentalDamage;
	physicalDamage = _physicalDamage;
	mentalResistance = _mentalResistance;
	physicalResistance = _physicalResistance;
}

NetworkEntityAttributeMessage::~NetworkEntityAttributeMessage()
{

}

sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityAttributeMessage& e)
{
	return packet << *((int*)&e.m_type) << e.id << e.strength << e.wits << e.fortitude << e.agility << e.towerConstruction << e.maxHealth << e.mentalDamage << e.mentalResistance << e.physicalDamage << e.physicalResistance;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkEntityAttributeMessage& e)
{
	return packet >> e.id >> e.strength >> e.wits >> e.fortitude >> e.agility >> e.towerConstruction >> e.maxHealth >> e.mentalDamage >> e.mentalResistance >> e.physicalDamage >> e.physicalResistance;
}