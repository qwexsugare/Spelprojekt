#pragma once
#include "networkmessage.h"
class NetworkEntityAttributeMessage : public NetworkMessage
{
public:
	NetworkEntityAttributeMessage();
	NetworkEntityAttributeMessage(unsigned int _id, int _strength, int _wits, int _fortitude, int _agility, int _towerConstruction,
		int _maxHealth, float _mentalDamage, float _physicalDamage, float _mentalResistance, float _physicalResistance);
	~NetworkEntityAttributeMessage();
	
	// Lol lol public vars saves a lot of time
	unsigned int id;
	int strength;
	int wits;
	int fortitude;
	int agility;
	int towerConstruction;
	int maxHealth;
	float mentalDamage;
	float physicalDamage;
	float mentalResistance;
	float physicalResistance;

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityAttributeMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEntityAttributeMessage& e);
};

