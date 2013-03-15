#pragma once
#include "networkmessage.h"
class NetworkEntityAttributeMessage : public NetworkMessage
{
private:
	unsigned int m_id;
	int m_health;
	int m_maxHealth;
	float m_mentalDamage;
	float m_physicalDamage;
	float m_mentalResistance;
	float m_physicalResistance;
public:
	NetworkEntityAttributeMessage();
	NetworkEntityAttributeMessage(unsigned int _id);
	NetworkEntityAttributeMessage(unsigned int _id, int _health, int _maxHealth, float _mentalDamage, float _physicalDamage, float _mentalResistance, float _physicalResistance);
	~NetworkEntityAttributeMessage();

	unsigned int getId();
	int getHealth();
	int getMaxHealth();
	float getMentalDamage();
	float getPhysicalDamage();
	float getMentalResistance();
	float getPhysicalResistance();

	friend sf::Packet& operator<<(sf::Packet& packet,const NetworkEntityAttributeMessage& e);
	friend sf::Packet& operator>>(sf::Packet& packet, NetworkEntityAttributeMessage& e);
};

